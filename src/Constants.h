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

// ticks per second
extern const int TICK_RATE;

#define TILE_SIZE 20

// map sizes in tiles
#define MAP_WIDTH 28
#define MAP_HEIGHT 31

// path to level files
extern const std::string LEVEL_PATH;

// path to skin images
extern const std::string SKINS_PATH;

#define ACTION_COUNT 4

// size of ghost/pacman
#define PLAYER_SIZE 2.0 * TILE_SIZE * 0.8

#define GHOST_COUNT 4
#define PLAYER_COUNT GHOST_COUNT + 1
