/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Game.h"
#include "App.h"
#include "Log.h"
#include "Error.h"
#include "Sounds.h"
#include "Object.h"
#include "GameState.h"
#include "BckgrObj.h"
#include "Pacman.h"
#include "Ghost.h"

#include <fstream>
#include <sstream>

extern Log logtxt;
extern App app;

#define PAC 1
#define MAPFILE "map"

#define STATE_GAME	0
#define STATE_STOPPED 4

void Game::changeSkin() {
    int i;
    for (i=0;i<NUMOFOBJECTS;i++) objects[i]->LoadTextures( SKINS_PATH );
}

bool Game::emptyMsgPump() {

    SDL_Event ev;

    while ( SDL_PollEvent(&ev) == 1 ) {
        switch(ev.type) {
        case SDL_KEYDOWN:
            switch (ev.key.keysym.sym ) {
            case SDLK_ESCAPE:
            case SDLK_q:
                return false;
            case SDLK_p:
                if ( getState() == STATE_GAME )
                    pause();
                break;
            case SDLK_f:
                toggleFps();
                break;
            case SDLK_UP:
            case SDLK_DOWN:
            case SDLK_LEFT:
            case SDLK_RIGHT:
            case SDLK_RETURN:
                processInput(ev.key.keysym.sym);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
    return true;
}

void Game::toggleSound() {

    if ( app.getSnd()->on) {
        app.getSnd()->toggleSounds();
    }
    else {
        app.getSnd()->toggleSounds();

        if (gamestarted && !ispaused ) app.getSnd()->play(10, 1);
        if (gamestarted && get_state()->get_vulnerable_ghost_count()>0 && !ispaused ) app.getSnd()->play(7, 1);
    }
}

void Game::setState(int st) {
    int i;

    if ( st == STATE_GAME ) {
        app.getSnd()->stop();
        app.getSnd()->play(10,1);

        for (i=0;i<NUMOFOBJECTS;i++) if (objects[i]) objects[i]->setAlpha(255);
        for (i=0;i<NUMOFOBJECTS;i++) if (objects[i]) objects[i]->setPaused( false);

    }
    else if ( st == STATE_STOPPED && state != STATE_STOPPED) {
        app.getSnd()->stop();
        app.getSnd()->play(0, 1);
        for (i=0;i<NUMOFOBJECTS;i++) if (objects[i]) objects[i]->setPaused( true);
        for (i=0;i<NUMOFOBJECTS;i++) if (objects[i]) objects[i]->setAlpha(255);
    }

    state = st;
}

void Game::logicGame() {
    if (get_state()->did_pacman_win() || get_state()->did_pacman_lose()) {
        assert(false); // TODO implement proper reaction to this
    }

    int actions[5] = {-1, -1, -1, -1, -1};
    for (int i=0; i<5; ++i) {
        for (int j=0; j<4; ++j) {
            if (game_state_info.legal_actions[i][j] > -1) {
                actions[i] = j;
                break;
            }
        }
    }
    game_state_info = get_state()->get_successor(walls, actions);
}

void Game::renderNormal() {
    // Note: might come in handy: SDL_GetTicks(); to make a more accurate delay
    app.delay(1000/TICK_RATE); // feel like life is flashing by, this helps fix that

    int i;
    std::ostringstream ostr;
    SDL_Color col;
    shared_ptr<SDL_Surface> txt;

    col.r = col.g = col.b = 255;

    // DRAW FIELD + SPRITES
    ((BckgrObj*)objects[0])->Draw(walls, get_state()->get_foods());
    ((Pacman*)objects[1])->Draw(get_state()->get_pacman_state());
    ((Ghost*)objects[2])->Draw(get_state()->get_ghost_state(0));
    ((Ghost*)objects[3])->Draw(get_state()->get_ghost_state(1));
    ((Ghost*)objects[4])->Draw(get_state()->get_ghost_state(2));
    ((Ghost*)objects[5])->Draw(get_state()->get_ghost_state(3));

    // DRAW SCORE + INFO
    for (i=1; i < get_state()->get_lives(); i++)
        objects[PAC]->Draw( 350+i*50, MAP_HEIGHT*TILE_SIZE+5);

    // display eaten fruit
    // objects[0]->Draw( MAP_WIDTH*TILE_SIZE - 40 -10, MAP_HEIGHT*TILE_SIZE +15 );

    ostr << "level: " << get_state()->get_level() << " score: " << get_state()->get_score();

    txt.reset(TTF_RenderText_Solid(font,ostr.str().c_str(),col), SDL_FreeSurface);
    if (!txt) throw_exception("DrawText failed");

    SDL_BlitSurface(txt.get(),NULL,app.getScreen().get(),&scorebox);

    // PAUSE
    if ( ispaused ) {
        SDL_Rect pauserect;
        pauserect.y = MAP_WIDTH*TILE_SIZE / 2 - 100;
        pauserect.w = 200;
        pauserect.x = MAP_HEIGHT*TILE_SIZE / 2 - 10;
        pauserect.h = 50;

        txt.reset(TTF_RenderText_Solid(font,"PAUSED",col), SDL_FreeSurface);
        if (!txt) throw_exception("DrawText failed");

        SDL_BlitSurface(txt.get(),NULL,app.getScreen().get(),&pauserect);
    }
}

bool Game::pause() {
    int i;

    if ( !ispaused ) {
        ispaused = true;
        app.getSnd()->stop();
        for (i=0;i<NUMOFOBJECTS;i++) objects[i]->setPaused( true);

        return ispaused;
    }
    else {
        ispaused = false;
        app.getSnd()->play(10, 1);
        if (get_state()->get_vulnerable_ghost_count() > 0) app.getSnd()->play(7, 1);
        for (i=0;i<NUMOFOBJECTS;i++) objects[i]->setPaused( false);

        return ispaused;
    }
}

void Game::gameInit() {
    int i;
    std::string tmpstr;

    isinit=false;
    app.getSnd()->stop();

    //resetting variables
    gamestarted = false;
    setState(STATE_GAME);

    if ( ispaused )
        pause();

    scorebox.x= 20;
    scorebox.w = 500;
    scorebox.y = MAP_HEIGHT * TILE_SIZE ;
    scorebox.h = 50;

    //DYNAMIC OBJECTS INIT
    if (walls!=NULL) {
        delete[] walls;
        walls=NULL;
    }
    for (i=0; i< NUMOFOBJECTS; i++) {
        if (objects[i]!=NULL) {
            delete objects[i];
            objects[i] = NULL;
        }
    }

    logtxt.print("Unloading complete");

    // INIT MAPS
    tmpstr = LEVEL_PATH;

    walls = new int[MAP_HEIGHT*MAP_WIDTH];
    loadMap(tmpstr + MAPFILE, walls);

    game_state_info = GameState::start_new_game(walls);

    logtxt.print("Maps loaded");

    //creating font

    if ( !font ) loadFont();

    logtxt.print("Font created");

    //loading level graphics

    objects[0] = new BckgrObj( app.getScreen(), 10 );
    objects[0]->LoadTextures(SKINS_PATH);

    logtxt.print("Level background loaded");

    logtxt.print("Sounds loaded");

    app.getSnd()->play(9, 0);

    setState( STATE_STOPPED);

    //create pacman + ghosts

    objects[1] = new Pacman(app.getScreen(), 20);
    objects[1]->LoadTextures(SKINS_PATH);

    objects[2] = new Ghost(app.getScreen(), 20, "1");
    objects[2]->LoadTextures(SKINS_PATH);

    objects[3] = new Ghost(app.getScreen(), 20, "2");
    objects[3]->LoadTextures(SKINS_PATH);

    objects[4] = new Ghost(app.getScreen(), 20, "3");
    objects[4]->LoadTextures(SKINS_PATH);

    objects[5] = new Ghost(app.getScreen(), 20, "4");
    objects[5]->LoadTextures(SKINS_PATH);

    logtxt.print("Objects loaded");

    render();

    emptyMsgPump();
    gamestarted = false;

    isinit = true;
}

void Game::processInput(int k, int ix, int iy) {
    if ( !gamestarted && !ispaused ) {
        gamestarted = true;
        if ( state == STATE_STOPPED || state == STATE_GAME )
            setState( STATE_GAME );
    }
}

void Game::processLogic() {
    // TODO rm intermediate
    logicGame();
}

void Game::loadMap(std::string file, int* memmap) {
    int i, count=0, size = MAP_HEIGHT * MAP_WIDTH;
    std::string tmp;
    char c('i');
    std::ifstream mp;

    mp.open( file.c_str() );

    if (!mp ) {
        throw_exception(file + " - Loading error");
    }

    for (i=0;i<size;i++) {
        do {
            if ( mp.eof() ) break;
            c=mp.get();
            if (c == '/' ) {	// enable comments in map file by prefixing line with  a slash
                getline(mp, tmp);
                continue;
            }
        }
        while (! (c >= '0' && c <= '9') ) ;
        memmap[i]=c-48;
        count++;
        if (!mp) break;
    }

    if ( mp.is_open() ) mp.close();

    if (count != size) {
        throw_exception(file + " - Loading error");
    }

    logtxt.print(file + " loaded");
}


std::string Game::getFPS() {
    unsigned int newtick = SDL_GetTicks();
    std::ostringstream ostr;
    float diff;

    diff = (float)(newtick-ticks) / (float)counter;	// ms per frame

    diff = 1000.0f / diff;			// frames per s

    ostr << diff << "fps";

    ticks = newtick;

    return ostr.str();
}

void Game::render() {
    shared_ptr<SDL_Surface>
            buf = app.getScreen(),
            txt;
    SDL_Color
            col;

    col.r = col.g = col.b = 255;

    if (counter == 100) {
        fps = getFPS();
        counter = 0;
    }

    if ( !renderisbusy ) {
        renderisbusy = true;

        renderNormal();

        if ( showfps ) {
            txt.reset(TTF_RenderText_Solid(font,fps.c_str(),col), SDL_FreeSurface);
            if (!txt) throw_exception("DrawText failed");

            SDL_BlitSurface(txt.get(),NULL,buf.get(),&fpsbox);
        }

        SDL_Flip(buf.get());

        renderisbusy = false;
        counter++;
    }
}

void Game::loadFont() {
    font = TTF_OpenFont("arial.ttf",24);
    if (!font)
        throw_exception("Failed to create font object ");

    logtxt.print("Font loaded");
}

void Game::PrepareShutdown() {
    int i;

    if ( font ) TTF_CloseFont(font);
    for (i=0;i<NUMOFOBJECTS;i++) if ( objects[i] ) delete objects[i];
}

Game::Game()
:   isinit(false),
    state(STATE_STOPPED),
    counter(0),
    font(NULL),
    walls(NULL),
    gamestarted(false),
    ispaused(false),
    showfps(false),
    renderisbusy(false)

{
    int i;

    fps = "loading";

    fpsbox.x= 10;
    fpsbox.w = 290;
    fpsbox.y = 10;
    fpsbox.h = 190;

    for (i=0;i<NUMOFOBJECTS;i++)
        objects[i] = NULL;

    for (i=0;i<10;i++)
        num[i]='0'+i;
}

Game::~Game()
{
    if (walls) delete[] walls;
}
