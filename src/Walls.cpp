/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Walls.h"
#include "Constants.h"

const int walls[MAP_HEIGHT * MAP_WIDTH] = {
    3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 3, 1, 1, 4, 0, 3, 1, 1, 1, 4, 0, 1, 1, 0, 3, 1, 1, 1, 4, 0, 3, 1, 1, 4, 0, 1,
    1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1,
    1, 0, 6, 1, 1, 5, 0, 6, 1, 1, 1, 5, 0, 6, 5, 0, 6, 1, 1, 1, 5, 0, 6, 1, 1, 5, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 3, 1, 1, 4, 0, 3, 4, 0, 3, 1, 1, 1, 1, 1, 1, 4, 0, 3, 4, 0, 3, 1, 1, 4, 0, 1,
    1, 0, 6, 1, 1, 5, 0, 1, 1, 0, 6, 1, 1, 4, 3, 1, 1, 5, 0, 1, 1, 0, 6, 1, 1, 5, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1,
    6, 1, 1, 1, 1, 4, 0, 1, 6, 1, 1, 4, 0, 1, 1, 0, 3, 1, 1, 5, 1, 0, 3, 1, 1, 1, 1, 5,
    0, 0, 0, 0, 0, 1, 0, 1, 3, 1, 1, 5, 0, 6, 5, 0, 6, 1, 1, 4, 1, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 3, 1, 1, 2, 2, 1, 1, 4, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 5, 0, 6, 5, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 6, 5, 0, 6, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 4, 0, 3, 4, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 3, 4, 0, 3, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 6, 1, 1, 1, 1, 1, 1, 5, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 3, 1, 1, 1, 1, 1, 1, 4, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0,
    3, 1, 1, 1, 1, 5, 0, 6, 5, 0, 6, 1, 1, 4, 3, 1, 1, 5, 0, 6, 5, 0, 6, 1, 1, 1, 1, 4,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 3, 1, 1, 4, 0, 3, 1, 1, 1, 4, 0, 1, 1, 0, 3, 1, 1, 1, 4, 0, 3, 1, 1, 4, 0, 1,
    1, 0, 6, 1, 4, 1, 0, 6, 1, 1, 1, 5, 0, 6, 5, 0, 6, 1, 1, 1, 5, 0, 1, 3, 1, 5, 0, 1,
    1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1,
    6, 1, 4, 0, 1, 1, 0, 3, 4, 0, 3, 1, 1, 1, 1, 1, 1, 4, 0, 3, 4, 0, 1, 1, 0, 3, 1, 8,
    3, 1, 5, 0, 6, 5, 0, 1, 1, 0, 6, 1, 1, 4, 3, 1, 1, 5, 0, 1, 1, 0, 6, 5, 0, 6, 1, 8,
    1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 3, 1, 1, 1, 1, 5, 6, 1, 1, 4, 0, 1, 1, 0, 3, 1, 1, 5, 6, 1, 1, 1, 1, 4, 0, 1,
    1, 0, 6, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 6, 5, 0, 6, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5
};
