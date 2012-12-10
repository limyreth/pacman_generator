/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "PlayerState.h"

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
