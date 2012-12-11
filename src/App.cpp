/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "App.h"
#include "Sounds.h"
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

void App::log_exception(const std::exception& e) {
    auto* file_name = boost::get_error_info<boost::throw_file>(e);
    auto* function_name = boost::get_error_info<boost::throw_function>(e);
    auto* line_number = boost::get_error_info<boost::throw_line>(e);

    std::ostringstream out;
    if (file_name) {
        // assume others are valid too iff file_name is valid
        out << *file_name <<  ":" << std::endl << *function_name << ":" << *line_number << ":" << std::endl;
    }
    out << e.what();

    std::cerr << out.str() << std::endl;
    logtxt.print(out.str());
}

void App::delay(unsigned int ms) {
    //return; // TODO use bool no_gui or inheritance or something to switch whether or not to delay. Should only delay when showing things in GUI
    SDL_Delay(10*ms);  // 10* for easier debugging TODO rm again
}

