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

static_assert(PLAYER_SIZE < 2.0 * TILE_SIZE, "Legal actions logic requires this");

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

    // To deal with rounding error, center us along the direction perpendicular
    // to our basic movement direction
    if (is_basic(action)) {
        if (is_vertical(action)) {
            pos.x = (get_tile_pos().x + 0.5) * TILE_SIZE;
        }
        else {
            pos.y = (get_tile_pos().y + 0.5) * TILE_SIZE;
        }
    }
}

// TODO rename to grid
IPoint PlayerState::get_tile_pos() const {
    return get_grid_pos(pos);
}

IPoint PlayerState::get_grid_pos(IPoint pos) const {
    return pos / TILE_SIZE;
}

/*
 * Get position in the grid that's offsetted by half a tile
 */
IPoint PlayerState::get_half_grid_pos() const {
    return (pos + IPoint(1, 1) * TILE_SIZE / 2.0) / TILE_SIZE;
}

