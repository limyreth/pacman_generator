/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "App.h"

extern Log logtxt;
extern Settings settings;

void App::InitWindow() {
    int bpp(32);

    if ( !settings.fieldwidth || !settings.fieldheight || !settings.tilesize ) {
        logtxt.print("fieldheight/fieldwidth/tilesize is not set, reverting to default window dimensions");
        std::cerr << "fieldheight/fieldwidth/tilesize is not set, reverting to default window dimensions";
    }
    else {
        settings.height=settings.fieldheight*settings.tilesize;
        settings.width=settings.fieldwidth*settings.tilesize;
    }

    screen.reset(SDL_SetVideoMode( settings.width,
                               settings.height+EXTRA_Y_SPACE,
                               bpp,         //bits per pixel; todo-make this dynamic
                               SDL_NOFRAME | SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_ANYFORMAT ), SDL_FreeSurface);

    if (screen == NULL)
        throw Error("Error while setting video mode");

    logtxt.print("Video mode set successfully");
}

void App::InitApp() {
    if ( SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0 )
        throw Error("Error while initializing SDL");

    logtxt.print("SDL systems initialized");

    if ( TTF_Init() < 0 )
        throw Error("Error while initializing SDL_ttf");

    logtxt.print("SDL_ttf initialized");
}

void App::InitSound() {
    snd = new Sounds();
    snd->init();
    snd->toggleSounds();  // start muted

    logtxt.print("Sound initialized");
}

void App::dot_eaten() {
    static unsigned int sound_counter = 0;
    getSnd()->play(1 + sound_counter%2, 0, -500);
    sound_counter++;
}

App::App()
:   quit(false),
    snd(NULL)
{
}

App::~App(void)
{
    if ( snd ) {
        delete snd;
        snd = NULL;
    }
}

void App::PrepareShutdown() {
    if ( TTF_WasInit() )
        TTF_Quit();

    SDL_Quit();
}

void App::log_exception(std::exception& e) {
    std::cerr << e.what() << std::endl;
    logtxt.print(e.what());
}
