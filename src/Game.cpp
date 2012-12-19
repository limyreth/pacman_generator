/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Game.h"
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

// debug
#include <iostream>
using std::cout;
using std::endl;

#define PAC 1
#define MAPFILE "map"

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
            case SDLK_f:
                toggleFps();
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

    app.getSnd()->toggleSounds();
    app.getSnd()->play(10, 1);
    if (get_state()->get_vulnerable_ghost_count()>0) app.getSnd()->play(7, 1);
}

void Game::logicGame() {
    if (get_state()->did_pacman_win() || get_state()->did_pacman_lose()) {
        assert(false); // TODO implement proper reaction to this
    }

    Action actions[PLAYER_COUNT] = {-1, -1, -1, -1, -1};
    for (int i=0; i<PLAYER_COUNT; ++i) {
        for (int j=0; j<4; ++j) {
            Action action = game_state_info.legal_actions[i][j];
            if (action > -1) {
                actions[i] = action;
                break;
            }
        }
    }
    game_state_info = get_state()->get_successor(actions, app);
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

    // draw node map
    pacman_nodes.draw(app.getScreen());
    //ghost_nodes.draw(app.getScreen());
}

void Game::gameInit() {
    int i;
    std::string tmpstr;

    isinit=false;
    app.getSnd()->stop();

    //resetting variables
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

    game_state_info = GameState::start_new_game(pacman_nodes.init(walls), ghost_nodes.init(walls));

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

    isinit = true;
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

    renderNormal();

    if ( showfps ) {
        txt.reset(TTF_RenderText_Solid(font,fps.c_str(),col), SDL_FreeSurface);
        if (!txt) throw_exception("DrawText failed");

        SDL_BlitSurface(txt.get(),NULL,buf.get(),&fpsbox);
    }

    SDL_Flip(buf.get());

    counter++;
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
    counter(0),
    font(NULL),
    walls(NULL),
    showfps(false)

{
    app.InitApp();
    app.InitWindow();
    app.InitSound();

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
