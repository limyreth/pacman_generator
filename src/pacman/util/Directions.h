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

namespace PACMAN {

namespace Direction {
    enum Type : int {
        ANY = -1,
        NORTH = 0,
        EAST = 1,
        SOUTH = 2,
        WEST = 3,
    };
}

extern const FPoint DIRECTIONS[];

}
