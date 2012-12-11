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

class GhostState : public PlayerState
{
public:
    enum State : unsigned char {
        NORMAL,
        VULNERABLE,
        DEAD
    };

public:
    GhostState();
    GhostState(IPoint spawn_pos);

    bool is_in_tunnel();

    virtual void get_legal_actions(const int* walls, Action action, Actions legal_actions, const PlayerState* old);

public:
    State state;

private:
    IPoint get_action_pos() const;
};
