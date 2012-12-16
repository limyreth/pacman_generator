/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "Point.h"
#include "Constants.h"

inline int at_wrap(int x, int y) {
    return y * MAP_WIDTH + (x % MAP_WIDTH);
}

inline int at(int x, int y) {
    return y * MAP_WIDTH + x;
}

inline int at(IPoint tile_pos) {
    return at(tile_pos.y, tile_pos.x);
}

