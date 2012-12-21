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
#include "GameStateInfo.h"
#include <sstream>
#include <assert.h>

namespace PACMAN {

    inline int at_wrap(int x, int y) {
        return y * MAP_WIDTH + (x % MAP_WIDTH);
    }

    inline int at(int x, int y) {
        assert(x >= 0);
        assert(x < MAP_WIDTH);
        assert(y >= 0);
        assert(y < MAP_HEIGHT);
        return y * MAP_WIDTH + x;
    }

    inline int at(IPoint tile_pos) {
        return at(tile_pos.y, tile_pos.x);
    }

    template <class T>
    inline std::string to_string(const T a) {
        std::ostringstream str;
        str << a;
        return str.str();
    }

    inline void print_legal_actions(MODEL::LegalActions legal_actions) {
        std::cout << (int)legal_actions.count << ", " << (int)legal_actions.reverse_action;
        std::cout << std::endl;
    }

}
