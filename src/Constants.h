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
static const int TICK_RATE = 60;

static const int TILE_SIZE = 20;

// map sizes in tiles
static const int MAP_WIDTH = 28;
static const int MAP_HEIGHT = 31;

// path to level files
static const std::string LEVEL_PATH = "./levels/0/";

// path to skin images
static const std::string SKINS_PATH = "./skins/minimal/";

static const int ACTION_COUNT = 4;

#define GHOST_COUNT 4
#define PLAYER_COUNT GHOST_COUNT + 1
