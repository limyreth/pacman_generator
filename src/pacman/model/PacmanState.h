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
#include "../Point.h"

namespace PACMAN {
    namespace MODEL {

        class PacmanState : public PlayerState
        {
        public:
            PacmanState();
            PacmanState(const Node* initial_node);
            PacmanState(std::istream& in);

            virtual void save(std::ostream& out) const;
            bool operator==(const PacmanState&) const;

            bool operator!=(const PacmanState& o) const {
                return !(*this == o);
            }
        };

    }
}
