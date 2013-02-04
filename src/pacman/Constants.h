/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "util/Point.h"

#include <string>

namespace PACMAN {

    namespace MODEL {
        // player indices
        extern const unsigned int PLAYER_PACMAN;

        // ghost indices (+1 to convert to player index)
        extern const unsigned int GHOST_BLINKY;
        extern const unsigned int GHOST_PINKY;
        extern const unsigned int GHOST_INKY;
        extern const unsigned int GHOST_CLYDE;

        // max allowable error on positions, due to floating point inaccuracies
        extern const float MAX_ROUNDING_ERROR;
    }

    namespace SPECIFICATION {
        // ticks per second
        extern const int TICK_RATE;

        extern const float NORMAL_PACMAN_SPEED;
        extern const float ENERGETIC_PACMAN_SPEED;
        extern const float GHOST_TUNNEL_SPEED;
        extern const float GHOST_VULNERABLE_SPEED;
        extern const float ELROY2_SPEED;
        extern const float ELROY1_SPEED;
        extern const float GHOST_NORMAL_SPEED;
        extern const float DEAD_GHOST_SPEED;

        // the amount of ticks ghosts are vulnerable
        extern const int VULNERABLE_TICKS;
        // the amount of ticks fruit stays on the map after spawning
        extern const int FRUIT_TICKS;
        // 100% speed expressed in tiles per tick.
        extern const float FULL_SPEED;

        // the max allowed ticks between releasing ghosts from the ghost pen
        // If exceeded, a ghost is forced to leave
        extern const int MAX_TICKS_BETWEEN_GHOST_RELEASE;

        // initial food count of start_foods, which is also the max
        extern const unsigned int MAX_FOOD_COUNT;
        extern const IPoint FRUIT_LEFT_TPOS;
        extern const IPoint FRUIT_RIGHT_TPOS;
        extern const FPoint FRUIT_POS;

        // size of ghost/pacman
        extern const float PLAYER_SIZE;
    }

    namespace GUI {
        // path to skin images
        extern const std::string SKINS_PATH;

        // pixel size of a tile, is best kept as a multiple of 8
        extern const int TILE_SIZE;

        // pixel size of ghost/pacman
        extern const float PLAYER_SIZE;
    }

}


// note: namespaces have no effect on defines, because preprocessor doesn't understand C++

// map sizes in tiles
#define MAP_WIDTH 28
#define MAP_HEIGHT 31

#define MAX_ACTION_COUNT 4

#define GHOST_COUNT 4u
#define PLAYER_COUNT (GHOST_COUNT + 1u)

