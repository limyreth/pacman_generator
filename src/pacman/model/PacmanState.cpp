/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "PacmanState.h"
#include "PacmanNodes.h"

namespace PACMAN {
    namespace MODEL {

PacmanState::PacmanState()
{
}

PacmanState::PacmanState(const Node* initial_node)
:   PlayerState(initial_node)
{
}

PacmanState::PacmanState(std::istream& in)
:   PlayerState(in, PACMAN_NODES)
{
}

void PacmanState::save(std::ostream& out) const {
    PlayerState::save(out, PACMAN_NODES);
}

    }
}
