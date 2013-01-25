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
#include "assertion.h"
#include "../Constants.h"
#include "../model/Action.h"

#include <sstream>

namespace PACMAN {

    inline int at(int x, int y) {
        REQUIRE(x >= 0);
        REQUIRE(x < MAP_WIDTH);
        REQUIRE(y >= 0);
        REQUIRE(y < MAP_HEIGHT);

        auto ret_val = y * MAP_WIDTH + x;

        ENSURE(ret_val < MAP_WIDTH * MAP_HEIGHT);
        return ret_val;
    }

    inline int at_wrap(int x, int y) {
        REQUIRE(x >= -1);
        REQUIRE(x <= MAP_WIDTH);
        if (x == -1) {
            x = MAP_WIDTH - 1;
        }
        else if (x == MAP_WIDTH) {
            x = 0;
        }
        return at(x, y);
    }

    inline int at(IPoint tile_pos) {
        return at(tile_pos.x, tile_pos.y);
    }

    template <class T>
    inline std::string to_string(const T a) {
        std::ostringstream str;
        str << a;
        return str.str();
    }

}
