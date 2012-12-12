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

PlayerState::PlayerState(IPoint pos) 
:   pos(pos)
{
}

/*
 * Move player by given action.
 *
 * Player will move at FULL_SPEED * speed_modifier.
 */
void PlayerState::move(Action action, double speed) {
    pos += action_to_direction(action) * speed;

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

    // TODO to deal with rounding error, when moving along the x-axis, center us vertically in tile. Analog for horizontal movement.
}

IPoint PlayerState::get_tile_pos() const {
    return pos / TILE_SIZE;
}

