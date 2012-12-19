/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class Game;
class Sounds;
class Object;
class UIHints;

#define NUMOFOBJECTS 6

class GUI
{
public:
    GUI(const Game& game);
    ~GUI();

    shared_ptr<UIHints> create_uihints();
    void render(const int* walls);
    bool emptyMsgPump();

private:
    void InitApp();
    void InitWindow();
    void InitSound();
    void loadFont();
    bool loadSprites();
    void loadMap(std::string file, int* memmap);

    void renderNormal(const int* walls);

    std::string getFPS();

    void toggleFps() { showfps = !showfps; }

    void toggleSound();

private:
    const Game& game;

    shared_ptr<SDL_Surface>
            screen,    //screen surface
            buf;       //buffer surface

    Sounds *snd;

    int
            counter;

    std::string
            fps;

    SDL_Rect
            fpsbox,
            scorebox;

    unsigned int
            ticks;

    TTF_Font
            *font;

    Object
            *objects[NUMOFOBJECTS];

    bool showfps;
};
