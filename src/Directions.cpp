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

//#define BASIC_ACTION_COUNT 4
bool is_basic(Action a) {
    //return a <= BASIC_ACTION_COUNT, then use bunch of arrays as maps opposite[action]=opposite_action, is_perpendicular[a][b]=bool; actions[8]=all of them; directions[action]=fpoint TODO is perhaps more performant. So if that part is a bottleneck with calgrind...
    return a == ActionFlags::NORTH || a == ActionFlags::EAST || a == ActionFlags::SOUTH || a == ActionFlags::WEST;
}

bool is_vertical(Action a) {
    return a & ActionFlags::Y_AXIS;
}

bool are_opposites(Action a, Action b) {
    return a != b && !are_perpendicular(a, b);
}

bool are_perpendicular(Action a, Action b) {
    return is_vertical(a) != is_vertical(b);
}
