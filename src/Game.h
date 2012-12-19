/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <SDL/SDL.h>  // TODO if many include Game.h, then this should be split off to elsewhere
#include <SDL/SDL_ttf.h>
#include "GameStateInfo.h"
#include "PacmanNodes.h"
#include "GhostNodes.h"

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class Sounds;
class GameState;
class Object;
class UIHints;

#define NUMOFOBJECTS 6

class Game
{
public:
    Game();
    ~Game();

    void InitApp();
    void InitWindow();
    void InitSound();
    void loadFont();
    bool loadSprites();
    void loadMap(std::string file, int* memmap);

    void render();
    void renderNormal();

    std::string getFPS();

    void processLogic();
    void logicGame();

    void toggleFps() { showfps = !showfps; }

    void toggleSound();
    bool emptyMsgPump();

private:
    inline shared_ptr<GameState> get_state() {
        return game_state_info.state;
    }

private:
    shared_ptr<UIHints> uihints;

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


    GameStateInfo game_state_info;

    int *walls;

    bool showfps;

    PacmanNodes pacman_nodes;
    GhostNodes ghost_nodes;
};
