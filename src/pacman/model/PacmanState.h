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
#include "../util/Point.h"

namespace PACMAN {
    namespace MODEL {

        class PacmanState : public PlayerState
        {
        public:
            PacmanState();
            PacmanState(const int origin_id, const int destination_id, FPoint pos); // Only for testing
            PacmanState(const Node& initial_node);

            double move(double distance, int player_index);
            virtual IPoint get_tile_pos() const;
            bool operator==(const PacmanState&) const;

            bool operator!=(const PacmanState& o) const {
                return !(*this == o);
            }

        protected:
            virtual const Nodes& get_nodes() const;
        };

    }
}
