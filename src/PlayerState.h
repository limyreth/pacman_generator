/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "Main.h"
#include "Point.h"
#include "Directions.h"

class PlayerState
{
public:
    PlayerState(SDL_Point pos);
    void move(int action, double speed_modifier);
    SDL_Point get_tile_pos() const;

    inline SDL_Point get_pixel_pos() const {
        return pos;
    }

private:
    SDL_Point pos;  // current position in pixels
};
