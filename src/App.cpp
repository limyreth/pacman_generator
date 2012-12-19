/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "App.h"
#include "NullSounds.h"
#include "DefaultSounds.h"
#include "Constants.h"
#include "Log.h"
#include "Error.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

extern Log logtxt;

void App::InitWindow() {
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

void App::InitApp() {
    if ( SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0 )
        throw_exception("Error while initializing SDL");

    logtxt.print("SDL systems initialized");

    if ( TTF_Init() < 0 )
        throw_exception("Error while initializing SDL_ttf");

    logtxt.print("SDL_ttf initialized");
}

void App::InitSound() {
    if (true) {  //TODO offer choice to turn it on
        // use disabled sound (!= muted)
        // This is handy for debugging (no more alsa underrun messages)
        snd = new NullSounds();
    }
    else {
        snd = new DefaultSounds();
    }

    logtxt.print("Sound initialized");
}

void App::dot_eaten() {
    static unsigned int sound_counter = 0;
    getSnd()->play(1 + sound_counter%2, 0, -500);
    sound_counter++;
}

App::App()
:   snd(NULL)
{
}

App::~App(void)
{
    delete snd;

    if ( TTF_WasInit() )
        TTF_Quit();
}

void App::delay(unsigned int ms) {
    //return; // TODO use bool no_gui or inheritance or something to switch whether or not to delay. Should only delay when showing things in GUI
    SDL_Delay(10*ms);  // 10* for easier debugging TODO rm again
}

