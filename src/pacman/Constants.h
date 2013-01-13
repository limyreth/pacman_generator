/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <string>

namespace PACMAN {
    namespace SPECIFICATION {
        // ticks per second
        extern const int TICK_RATE;

        extern const double NORMAL_PACMAN_SPEED;
        extern const double ENERGETIC_PACMAN_SPEED;
        extern const double GHOST_TUNNEL_SPEED;
        extern const double GHOST_VULNERABLE_SPEED;
        extern const double ELROY2_SPEED;
        extern const double ELROY1_SPEED;
        extern const double GHOST_NORMAL_SPEED;
        // the amount of ticks ghosts are vulnerable
        extern const int VULNERABLE_TICKS;
        // the amount of ticks fruit stays on the map after spawning
        extern const int FRUIT_TICKS;
        // 100% speed expressed in tiles per tick.
        extern const double FULL_SPEED;
    }

    namespace GUI {
        // path to skin images
        extern const std::string SKINS_PATH;
    }
}


// note: namespaces have no effect on defines, because preprocessor doesn't understand C++

#define TILE_SIZE 20

// map sizes in tiles
#define MAP_WIDTH 28
#define MAP_HEIGHT 31

#define MAX_ACTION_COUNT 4

// size of ghost/pacman
#define PLAYER_SIZE (2.0 * TILE_SIZE * 0.8)

#define GHOST_COUNT 4
#define PLAYER_COUNT (GHOST_COUNT + 1)

#define GHOST_BLINKY 0
#define GHOST_PINKY 1
#define GHOST_INKY 2
#define GHOST_CLYDE 3
