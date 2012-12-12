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
    PlayerState(IPoint pos);
    void move(Action action, double speed);
    IPoint get_tile_pos() const;
    IPoint get_half_grid_pos() const;

    inline IPoint get_pixel_pos() const {
        return pos;
    }

    virtual void get_legal_actions(const int* walls, Action action, Actions legal_actions, const PlayerState* old) = 0;

protected:
    IPoint get_grid_pos(IPoint pos) const;

private:
    IPoint pos;  // current position in pixels
};
