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
    GhostState(SDL_Point spawn_pos);

    bool is_in_tunnel();

public:
    State state;
};
