/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once
#include <vector>
#include <string>
#include <cstdlib>
#include <sys/stat.h>
#include "Main.h"

using std::string;

class Settings {
public:
    Settings();

    bool LoadSettings(string filename);

    //searches for str in level/skinspaths; if successful, sets currently selected path.
    //returns 0 on success, 1 on failure
    int setPath(int mode, string str);

    //////////////////////////////
    // VARIABLES	- APP
    //////////////////////////////
    int
            width,
            height;

    //////////////////////////////
    // VARIABLES	- GAME
    //////////////////////////////

    const int TICK_RATE;  // ticks per second
    const int PLAYER_SIZE;  // drawing size of ghost/pacman
    const int tilesize;  // TODO rename TILE_SIZE
    const int VULNERABLE_TICKS;  // the amount of ticks ghosts are vulnerable
    const int FRUIT_TICKS;  // the amount of ticks fruit stays on the map after spawning

    int
            fieldwidth,
            fieldheight,
            gatex,
            gatey,
            pacstartx,
            pacstarty,
            baddiestartx,
            baddiestarty,

            lvlpathcount,
            lvlpathcurrent,
            skinspathcount,
            skinspathcurrent,
            full_speed;  // 100% speed expressed in px per tick.

    std::vector<string>
            lvlpath,
            skinspath,
            searchpaths;

    /* look for file in search paths and return first instance */
    string getFile(string filename);
};
