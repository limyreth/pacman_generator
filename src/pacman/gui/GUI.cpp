/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "GUI.h"
#include "Sounds.h"
#include "Object.h"
#include "BckgrObj.h"
#include "Pacman.h"
#include "Ghost.h"
#include "NullSounds.h"
#include "DefaultSounds.h"
#include "GameStateObserver.h"
#include "SDLUtility.h"
#include "../Constants.h"
#include "../util/error.h"
#include "../model/GameState.h"
#include "../model/PacmanNodes.h"
#include "../model/GhostNodes.h"
#include "../specification/Walls.h"

#include <sstream>
#include <SDL/SDL_gfxPrimitives.h>

#define PAC 1

using namespace ::PACMAN::SPECIFICATION;
using ::PACMAN::MODEL::TILE_SIZE;
using std::cout;
using std::endl;
using std::shared_ptr;

namespace PACMAN {
    namespace GUI {

GUI::GUI(GUIArgs gui_args)
:   preferred_direction(Direction::NORTH),
    gui_args(gui_args),
    paused(false)
{
    InitApp();
    InitWindow();
    InitSound();

    old_ticks = SDL_GetTicks();

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
}

void GUI::InitApp() {
    if ( SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0 )
        throw_exception("Error while initializing SDL");

    if ( TTF_Init() < 0 )
        throw_exception("Error while initializing SDL_ttf");
}

void GUI::InitSound() {
    if (true) {
        // use disabled sound (!= muted)
        // This is handy for debugging (no more alsa underrun messages)
        snd.reset(new NullSounds());
    }
    else {
        snd.reset(new DefaultSounds());
    }
}

bool GUI::should_stop() {
    if (is_paused()) {
        delay(100);
    }
    return !handle_events();
}

bool GUI::handle_events() {
    SDL_Event ev;

    while ( SDL_PollEvent(&ev) == 1 ) {
        switch(ev.type) {
        case SDL_KEYDOWN:
            switch (ev.key.keysym.sym ) {

            case SDLK_p:
                paused = !paused;
                break;

            case SDLK_ESCAPE:
            case SDLK_q:
                return false;

            case SDLK_UP:
                preferred_direction = Direction::NORTH;
                break;

            case SDLK_RIGHT:
                preferred_direction = Direction::EAST;
                break;

            case SDLK_DOWN:
                preferred_direction = Direction::SOUTH;
                break;

            case SDLK_LEFT:
                preferred_direction = Direction::WEST;
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

Direction::Type GUI::get_preferred_direction() {
    return preferred_direction;
}

void GUI::toggleSound() {
    snd->toggleSounds();
    snd->play(10, 1);
}

void GUI::finished_step(const MODEL::GameState& state) {
    render(state);
}

void GUI::render(const MODEL::GameState& state) {
    // enforce fixed frame/tick rate
    {
        const Uint32 new_ticks = SDL_GetTicks();
        int delay_ticks = 1000/(TICK_RATE * gui_args.game_speed) - (int)(new_ticks - old_ticks);
        if (delay_ticks > 0) {
            delay(delay_ticks);
        }
        old_ticks = new_ticks;
    }

    int i;
    std::ostringstream ostr;
    SDL_Color col;
    shared_ptr<SDL_Surface> txt;

    col.r = col.g = col.b = 255;

    // DRAW FIELD + SPRITES
    ((BckgrObj*)objects[0])->Draw(state.get_foods(), state.is_fruit_spawned(), gui_args.show_food);
    ((Pacman*)objects[1])->Draw((const MODEL::PacmanState&)state.get_player(0));
    for (int i=0; i<GHOST_COUNT; ++i) {
        ((Ghost*)objects[i+2])->Draw((const MODEL::GhostState&)state.get_player(i+1));
    }

    // DRAW SCORE + INFO
    for (i=1; i < state.get_lives(); i++)
        objects[PAC]->Draw( 350+i*50, MAP_HEIGHT*TILE_SIZE+5);

    // display eaten fruit
    // objects[0]->Draw( MAP_WIDTH*TILE_SIZE - 40 -10, MAP_HEIGHT*TILE_SIZE +15 );

    ostr << "level: " << state.get_level() << " score: " << state.get_score();

    txt.reset(TTF_RenderText_Solid(font,ostr.str().c_str(),col), SDL_FreeSurface);
    if (!txt) throw_exception("DrawText failed");

    SDL_BlitSurface(txt.get(),NULL,screen.get(),&scorebox);

    // draw node map
    if (gui_args.show_pacman_nodes) {
        MODEL::PACMAN_NODES.draw(screen);
    }
    if (gui_args.show_ghost_nodes) {
        MODEL::GHOST_NODES.draw(screen);
    }

    if (gui_args.show_respawn_paths) {
        MODEL::GHOST_NODES.draw_respawn_paths(screen);
    }

    if (gui_args.show_grid) {
        Uint32 grid_color = 0x0000FF99;

        // vertical lines
        for (int x = 0; x < MAP_WIDTH; ++x) {
            int retval = lineColor(screen.get(), TILE_SIZE * x, 0, TILE_SIZE * x, TILE_SIZE * MAP_HEIGHT, grid_color);
            ASSERT(retval == 0);
        }

        // horizontal lines
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            int retval = lineColor(screen.get(), 0, TILE_SIZE * y, TILE_SIZE * MAP_WIDTH, TILE_SIZE * y, grid_color);
            ASSERT(retval == 0);
        }
    }

    SDL_Flip(screen.get());
}

void GUI::loadFont() {
    font = TTF_OpenFont("arial.ttf",24);
    if (!font)
        throw_exception("Failed to create font object ");
}

shared_ptr<MODEL::GameStateObserver> GUI::create_state_observer() {
    return shared_ptr<MODEL::GameStateObserver>(new GameStateObserver(snd));
}

bool GUI::is_paused() {
    return paused;
}

void GUI::pause() {
    paused = true;
}

}}
