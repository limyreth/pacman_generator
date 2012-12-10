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

    screen.reset(SDL_SetVideoMode( settings.width,
                               settings.height+EXTRA_Y_SPACE,
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

#include <boost/exception/all.hpp>
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

