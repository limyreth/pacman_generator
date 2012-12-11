/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "Point.h"
#include "GameStateInfo.h"

class PlayerState
{
public:
    PlayerState(SDL_Point pos);
    void move(int action, double speed);
    SDL_Point get_tile_pos() const;

    inline SDL_Point get_pixel_pos() const {
        return pos;
    }

    virtual void get_legal_actions(const int* walls, Action action, Actions legal_actions, const PlayerState* old) = 0;

protected:
    SDL_Point pos;  // current position in pixels
};
