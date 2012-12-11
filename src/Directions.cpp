/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Directions.h"
#include <cmath>

namespace ActionFlags {
    Action NORTH = 1;
    Action EAST = 2;
    Action SOUTH = 4;
    Action WEST = 8;
}

const Action BASIC_ACTIONS[] = {
    ActionFlags::NORTH,
    ActionFlags::EAST,
    ActionFlags::SOUTH,
    ActionFlags::WEST
};

FPoint action_to_direction(Action action) {
    assert(action > 0);

    FPoint direction;

    if (action & ActionFlags::NORTH) {
        direction.y = -1.0;
    }
    else if (action & ActionFlags::SOUTH) {
        direction.y = 1.0;
    }

    if (action & ActionFlags::EAST) {
        direction.x = 1.0;
    }
    else if (action & ActionFlags::WEST) {
        direction.x = -1.0;
    }

    // normalize
    direction /= sqrt(direction.x * direction.x + direction.y * direction.y);

    return direction;
}
