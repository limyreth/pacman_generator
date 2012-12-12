/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "PlayerState.h"
#include "Point.h"

class PacmanState : public PlayerState
{
public:
    PacmanState(IPoint spawn_pos);

    virtual void get_legal_actions(const int* walls, Action action, Actions legal_actions, const PlayerState* old);

private:
    bool is_cornering(Action action) const;
    bool must_continue(Action action, const PlayerState* old) const;
    IPoint get_bound_pos(FPoint direction) const;
};
