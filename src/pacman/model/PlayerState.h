/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "../Point.h"
#include "GameStateInfo.h"
#include "../Directions.h"

namespace PACMAN {
    namespace MODEL {

        class Node;

        class PlayerState
        {
        public:
            PlayerState();
            PlayerState(const Node* initial_node);
            void move(double distance, Action next_action);
            IPoint get_tile_pos() const;

            inline FPoint get_pixel_pos() const {
                return pos;
            }

            // what are legal next actions to a next move() call
            void get_legal_actions(LegalActions& legal_actions) const;

            Action get_action_along_direction(Direction::Type direction) const;

        private:
            void move(double distance);
            void invariants() const;

        private:
            FPoint pos;  // current position in pixels
            const Node* origin;  // we come from this node
            const Node* destination;  // we are moving towards this node
            bool must_repeat_previous_action;
        };

    }
}
