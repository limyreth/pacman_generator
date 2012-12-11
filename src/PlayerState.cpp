/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "PlayerState.h"
#include "Directions.h"
#include "Constants.h"
#include <assert.h>

#include "Utility.h"

extern Directions DIRECTIONS;

PlayerState::PlayerState(SDL_Point pos) 
:   pos(pos)
{
}

/*
 * Move player by given action.
 *
 * Player will move at FULL_SPEED * speed_modifier.
 */
void PlayerState::move(int action, double speed) {
    assert(action >= 0);
    assert(action < ACTION_COUNT);

    pos += DIRECTIONS[action] * speed;

    // wrap screen when hitting left/right edge of tunnel
    auto tpos = get_tile_pos();
    if (tpos.x < 0) {
        pos.x = MAP_WIDTH * TILE_SIZE - pos.x;
        assert(get_tile_pos().x < MAP_WIDTH); // TODO rm after testing
    }
    else if (tpos.x >= MAP_WIDTH) {
        pos.x -= MAP_WIDTH * TILE_SIZE;
        assert(get_tile_pos().x > 0); // TODO rm after testing
    }
}

SDL_Point PlayerState::get_tile_pos() const {
    return pos / TILE_SIZE;
}

void PlayerState::get_legal_actions(const int* walls, Action action, Actions legal_actions, const PlayerState* old) {
        SDL_Point tpos = get_tile_pos();

        SDL_Point old_tpos;
        if (old) {
            old_tpos = old->get_tile_pos();
        }
        else {
            // set previous pos to an invalid pos
            old_tpos = SDL_Point(-1, -1);
        }

        // TODO ghosts should be offered a change of direction only when they are about to cross the center of a tile, rather than the edge
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
                auto new_tpos = tpos + DIRECTIONS[i];
                bool is_legal_tpos = walls[at(new_tpos)] == 0 || new_tpos.x < 0 || new_tpos.x == MAP_WIDTH;
                legal_actions[i] = is_legal_tpos ? i : -1;
            }
            // TODO order reverse direction as last (swap its value with that of the last)
        }
}
