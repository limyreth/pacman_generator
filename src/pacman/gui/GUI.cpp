/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "GUI.h"
#include "../Game.h"
#include "../Log.h"
#include "../Error.h"
#include "Sounds.h"
#include "Object.h"
#include "../model/GameState.h"
#include "BckgrObj.h"
#include "Pacman.h"
#include "Ghost.h"
#include "NullSounds.h"
#include "DefaultSounds.h"
#include "../Constants.h"
#include "GUIHints.h"
#include "SDLUtility.h"
#include "../model/PacmanNodes.h"
#include "../model/GhostNodes.h"
#include "../specification/Walls.h"

#include <sstream>

#define PAC 1

namespace PACMAN {
    using namespace SPECIFICATION;

    namespace GUI {

GUI::GUI(Game& game)
:   counter(0),
    showfps(false),
    game(game)
{
    InitApp();
    InitWindow();
    InitSound();

    fps = "loading";

    fpsbox.x= 10;
    fpsbox.w = 290;
    fpsbox.y = 10;
    fpsbox.h = 190;

    scorebox.x= 20;
    scorebox.w = 500;
    scorebox.y = MAP_HEIGHT * TILE_SIZE ;
    scorebox.h = 50;

    loadFont();

    snd->play(9, 0);

    objects[0] = new BckgrObj( screen, 10 );
    objects[0]->LoadTextures(SKINS_PATH);

    objects[1] = new Pacman(screen, 20);
    objects[1]->LoadTextures(SKINS_PATH);

    objects[2] = new Ghost(screen, 20, "1");
    objects[2]->LoadTextures(SKINS_PATH);

    objects[3] = new Ghost(screen, 20, "2");
    objects[3]->LoadTextures(SKINS_PATH);

    objects[4] = new Ghost(screen, 20, "3");
    objects[4]->LoadTextures(SKINS_PATH);

    objects[5] = new Ghost(screen, 20, "4");
    objects[5]->LoadTextures(SKINS_PATH);
}

GUI::~GUI()
{
    if (font) 
        TTF_CloseFont(font);

    for (int i=0; i<NUMOFOBJECTS; i++) 
        if (objects[i]) 
            delete objects[i];

    if (TTF_WasInit())
        TTF_Quit();
}

void GUI::InitWindow() {
    int bpp(32);

    const int width = MAP_WIDTH * TILE_SIZE;
    const int height = MAP_HEIGHT * TILE_SIZE + 50;
    screen.reset(SDL_SetVideoMode(width,
                               height,
                               bpp,         //bits per pixel; todo-make this dynamic
                               SDL_NOFRAME | SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_ANYFORMAT ), SDL_FreeSurface);

    if (screen == NULL)
        throw_exception("Error while setting video mode");

    logtxt.print("Video mode set successfully");
}

void GUI::InitApp() {
    if ( SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0 )
        throw_exception("Error while initializing SDL");

    logtxt.print("SDL systems initialized");

    if ( TTF_Init() < 0 )
        throw_exception("Error while initializing SDL_ttf");

    logtxt.print("SDL_ttf initialized");
}

void GUI::InitSound() {
    if (true) {  //TODO offer choice to turn it on
        // use disabled sound (!= muted)
        // This is handy for debugging (no more alsa underrun messages)
        snd.reset(new NullSounds());
    }
    else {
        snd.reset(new DefaultSounds());
    }

    logtxt.print("Sound initialized");
}

bool GUI::emptyMsgPump() {

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

void GUI::toggleSound() {

    snd->toggleSounds();
    snd->play(10, 1);
    if (game.get_state()->get_vulnerable_ghost_count()>0) snd->play(7, 1);
}

void GUI::renderNormal() {
    // Note: might come in handy: SDL_GetTicks(); to make a more accurate delay
    delay(1000/TICK_RATE); // feel like life is flashing by, this helps fix that

    int i;
    std::ostringstream ostr;
    SDL_Color col;
    shared_ptr<SDL_Surface> txt;

    col.r = col.g = col.b = 255;

    auto state = game.get_state();

    // DRAW FIELD + SPRITES
    ((BckgrObj*)objects[0])->Draw(walls, state->get_foods());
    ((Pacman*)objects[1])->Draw((const MODEL::PacmanState&)state->get_player(0));
    for (int i=0; i<GHOST_COUNT; ++i) {
        ((Ghost*)objects[i+2])->Draw((const MODEL::GhostState&)state->get_player(i+1));
    }

    // DRAW SCORE + INFO
    for (i=1; i < state->get_lives(); i++)
        objects[PAC]->Draw( 350+i*50, MAP_HEIGHT*TILE_SIZE+5);

    // display eaten fruit
    // objects[0]->Draw( MAP_WIDTH*TILE_SIZE - 40 -10, MAP_HEIGHT*TILE_SIZE +15 );

    ostr << "level: " << state->get_level() << " score: " << state->get_score();

    txt.reset(TTF_RenderText_Solid(font,ostr.str().c_str(),col), SDL_FreeSurface);
    if (!txt) throw_exception("DrawText failed");

    SDL_BlitSurface(txt.get(),NULL,screen.get(),&scorebox);

    // draw node map
    //PACMAN_NODES.draw(screen);
    //GHOST_NODES.draw(screen);
}

std::string GUI::getFPS() {
    unsigned int newtick = SDL_GetTicks();
    std::ostringstream ostr;
    float diff;

    diff = (float)(newtick-ticks) / (float)counter;	// ms per frame

    diff = 1000.0f / diff;			// frames per s

    ostr << diff << "fps";

    ticks = newtick;

    return ostr.str();
}

void GUI::render() {
    shared_ptr<SDL_Surface>
            buf = screen,
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

void GUI::loadFont() {
    font = TTF_OpenFont("arial.ttf",24);
    if (!font)
        throw_exception("Failed to create font object ");
}

shared_ptr<MODEL::UIHints> GUI::create_uihints() {
    return shared_ptr<MODEL::UIHints>(new GUIHints(snd));
}

    }
}
