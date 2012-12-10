/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "PlayerState.h"

extern Settings settings;
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
void PlayerState::move(int action, double speed_modifier) {

    pos += DIRECTIONS[action] * (settings.full_speed * speed_modifier);

    // wrap screen when hitting left/right edge of tunnel
    auto tpos = get_tile_pos();
    if (tpos.x < 0) {
        pos.x = settings.fieldwidth * settings.tilesize - pos.x;
        assert(get_tile_pos().x < settings.fieldwidth); // TODO rm after testing
    }
    else if (tpos.x >= settings.fieldwidth) {
        pos.x -= settings.fieldwidth * settings.tilesize;
        assert(get_tile_pos().x > 0); // TODO rm after testing
    }
}

SDL_Point PlayerState::get_tile_pos() const {
    return pos / settings.tilesize;
}
