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
#include "PlayerState.h"
#include "Point.h"

class PacmanState : public PlayerState
{
public:
    PacmanState(SDL_Point spawn_pos);
};
