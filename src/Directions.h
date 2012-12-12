/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "GameStateInfo.h"
#include "Point.h"

namespace ActionFlags {
    const Action X_AXIS = 0; // TODO extern
    const Action Y_AXIS = 16;
    const Action NORTH = 1 + Y_AXIS;
    const Action EAST = 2 + X_AXIS;
    const Action SOUTH = 4 + Y_AXIS;
    const Action WEST = 8 + X_AXIS;
}

extern const Action BASIC_ACTIONS[];

FPoint action_to_direction(Action action);

bool is_basic(Action a);

// Note: only works for basic actions
bool is_vertical(Action a);

// Note: only works for basic actions
bool are_opposites(Action a, Action b);

// Note: only works for basic actions
bool are_perpendicular(Action a, Action b);
