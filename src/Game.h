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
#include "App.h"

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class GameState;
class Object;

#define NUMOFOBJECTS 6

class Game
{
public:
    Game();
    ~Game();

    void loadFont();
    bool loadSprites();
    void loadMap(std::string file, int* memmap);

    void render();
    void renderNormal();

    std::string getFPS();

    void processInput(int k, int ix = -1, int iy = -1);
    void processLogic();
    void logicGame();

    void resetLvl();
    void nextLvl();
    void gameInit();

    bool pause();

    int  getState() { return state; }
    void setState( int st);

    void toggleFps() { showfps = !showfps; }

    bool isinit;

    void toggleSound();
    bool emptyMsgPump();
    void changeSkin();

    void PrepareShutdown();

private:
    inline shared_ptr<GameState> get_state() {
        return game_state_info.state;
    }

private:
    int
            state,
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

    int
            *walls,
            key;

    bool
            gamestarted,
            ispaused,
            showfps,
            renderisbusy;

    std::string
            num[10];


    PacmanNodes pacman_nodes;
    GhostNodes ghost_nodes;
    App app;
};
