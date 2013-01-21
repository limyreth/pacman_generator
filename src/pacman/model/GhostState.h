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

namespace PACMAN {
    namespace MODEL {

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
            GhostState(const Node* initial_node);

            double move(double distance, int player_index);
            void die();
            bool is_in_tunnel();

            bool operator==(const GhostState&) const;

            bool operator!=(const GhostState& o) const {
                return !(*this == o);
            }

        public:
            State state;
        };

    }
}
