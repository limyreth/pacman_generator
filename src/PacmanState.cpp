/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "PacmanState.h"
#include "Utility.h"
#include "Directions.h"

PacmanState::PacmanState(IPoint spawn_pos)
:   PlayerState(spawn_pos)
{
}

void PacmanState::get_legal_actions(const int* walls, Action action, Actions legal_actions, const PlayerState* old) {
    IPoint tpos = get_tile_pos();

    IPoint old_tpos;
    if (old) {
        old_tpos = old->get_tile_pos();
    }
    else {
        // set previous pos to an invalid pos
        old_tpos = IPoint(-1, -1);
    }

    // TODO add a pacman.cornering bool that's set to true when pacman is changing direction
    if (tpos == old_tpos) {
        // Next action has to be the same as current action
        legal_actions[0] = action;
        for (int i=1; i<ACTION_COUNT; ++i) {
            legal_actions[i] = -1;
        }
    }
    else {
        // Any nonobstructed path is fine
        for (int i=0; i<ACTION_COUNT; ++i) {
            IPoint new_tpos = tpos + action_to_direction(BASIC_ACTIONS[i]);
            bool is_legal_tpos = walls[at(new_tpos)] == 0 || new_tpos.x < 0 || new_tpos.x == MAP_WIDTH;
            if (is_legal_tpos) {
                legal_actions[i] = BASIC_ACTIONS[i];
            }
            else {
                legal_actions[i] = 0;
            }
        }
        // TODO order reverse direction as last (swap its value with that of the last)
    }
}
