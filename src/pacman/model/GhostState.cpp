/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "GhostState.h"
#include "../Utility.h"

// TODO dead ghost takes shortest path back to correct pen tile

// TODO size enums to 1 byte

namespace PACMAN {
    namespace MODEL {

GhostState::GhostState()
{
}

GhostState::GhostState(const Node* initial_node)
:   PlayerState(initial_node), state(NORMAL)
{
}

bool GhostState::is_in_tunnel() {
    return false; // TODO implement this damn it
}

// Note: this has little meaning other than that when it changes, a new action may be chosen (which is by crossing any grid line with offset half a tile)

    }
}
