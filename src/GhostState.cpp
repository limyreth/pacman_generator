/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "GhostState.h"
#include "Utility.h"
#include "Directions.h"

// TODO dead ghost takes shortest path back to correct pen tile

// TODO size enums to 1 byte
GhostState::GhostState()  // the infamous random garble 'initializer'
: GhostState(IPoint()) 
{
}

GhostState::GhostState(IPoint spawn_pos)
:   PlayerState(spawn_pos), state(NORMAL)
{
}

bool GhostState::is_in_tunnel() {
    return false; // TODO implement this damn it
}

// Note: this has little meaning other than that when it changes, a new action may be chosen (which is by crossing any grid line with offset half a tile)

void GhostState::get_legal_actions(const int* walls, Action action, Actions legal_actions, const PlayerState* old) {
    IPoint apos = get_half_grid_pos();

    IPoint old_apos;
    if (old) {
        old_apos = ((GhostState*)old)->get_half_grid_pos();
    }
    else {
        // set previous pos to an invalid pos
        old_apos = IPoint(-1, -1);
    }

    if (apos == old_apos) {
        // Next action has to be the same as current action
        legal_actions[0] = action;
        for (int i=1; i<ACTION_COUNT; ++i) {
            legal_actions[i] = -1;
        }
    }
    else {
        IPoint tpos = get_tile_pos();
        // Any nonobstructed path is fine
        for (int i=0; i<ACTION_COUNT; ++i) {
            Action action = BASIC_ACTIONS[i];
            IPoint new_tpos = tpos + action_to_direction(action);
            bool is_legal_tpos = walls[at(new_tpos)] == 0 || new_tpos.x < 0 || new_tpos.x == MAP_WIDTH;
            legal_actions[i] = is_legal_tpos ? action : 0;
        }
        // TODO order reverse direction as last (swap its value with that of the last)
    }
}
