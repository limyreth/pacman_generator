/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Constants.h"

namespace PACMAN {

    namespace MODEL {
        const unsigned int PLAYER_PACMAN = 0u;
        const unsigned int GHOST_BLINKY = 0u;
        const unsigned int GHOST_PINKY = 1u;
        const unsigned int GHOST_INKY = 2u;
        const unsigned int GHOST_CLYDE = 3u;

        const float MAX_ROUNDING_ERROR = 1e-3f;
    }

    namespace SPECIFICATION {
        const int TICK_RATE = 60;

        const float NORMAL_PACMAN_SPEED = 0.8f;
        const float ENERGETIC_PACMAN_SPEED = 0.9f;
        const float GHOST_TUNNEL_SPEED = 0.4f;
        const float GHOST_VULNERABLE_SPEED = 0.5f;
        const float ELROY2_SPEED = 0.85f;
        const float ELROY1_SPEED = 0.8f;
        const float GHOST_NORMAL_SPEED = 0.75f;
        const float DEAD_GHOST_SPEED = 2.0f * NORMAL_PACMAN_SPEED;

        const int VULNERABLE_TICKS = 6 * TICK_RATE;
        const int FRUIT_TICKS = 10 * TICK_RATE;
        const float FULL_SPEED = 9.5f / TICK_RATE;

        const unsigned int MAX_FOOD_COUNT = 244u;

        const IPoint FRUIT_LEFT_TPOS(13, 17);
        const IPoint FRUIT_RIGHT_TPOS(14, 17);
        const FPoint FRUIT_POS(14, 17.5);

        const int MAX_TICKS_BETWEEN_GHOST_RELEASE = 4 * TICK_RATE;  // 4 seconds

        const float PLAYER_SIZE = 2.0f * 0.8f;
    }

    namespace GUI {
        const std::string SKINS_PATH = "./skins/minimal/";
        const int TILE_SIZE = 24;
        const float PLAYER_SIZE = ::PACMAN::SPECIFICATION::PLAYER_SIZE * TILE_SIZE;
    }

}
