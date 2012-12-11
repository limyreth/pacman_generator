/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once
#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class Sounds;
class SDL_Surface;

class App
{
public:
    App();
    ~App();             //SDL systems are shut down in destructor

    void InitApp();     //SDL systems are initialized
    void InitWindow();  //creates window with parameters from loaded settings file
    void InitSound();
    void PrepareShutdown();

    //////////////
    //Global
    //////////////

    shared_ptr<SDL_Surface> getScreen() const { return screen; }
    shared_ptr<SDL_Surface> getBuf() const { return buf; }
    Sounds* getSnd() { return snd; }
    void dot_eaten();
    void delay(unsigned int ms);
    void log_exception(const std::exception& e);

private:

    //////////////
    //Global
    //////////////

    bool
            quit;       //if true then quit application

    shared_ptr<SDL_Surface>
            screen,    //screen surface
            buf;       //buffer surface

    Sounds
            *snd;

};
