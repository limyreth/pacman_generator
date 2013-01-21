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
#include "Action.h"
#include "../Directions.h"

namespace PACMAN {
    namespace MODEL {

        class Node;
        class Nodes;

        class PlayerState : public ASSERTION::Assertable
        {
        public:
            PlayerState();
            PlayerState(const Node* initial_node);
            virtual double move(double distance, int player_index);
            virtual void act(Action action);
            virtual IPoint get_tile_pos() const;

            inline FPoint get_pixel_pos() const {
                return pos;
            }

            /*
             * the count of valid actions for a call to act()
             *
             * Valid actions are 0 <= action <= count
             */
            unsigned char get_action_count() const;

            Action get_action_along_direction(Direction::Type direction) const;

            void set_allow_reversing(bool allow);

        protected:
            const FPoint& get_pos() const;
            void invariants() const;
            void save(std::ostream& out, const Nodes& nodes) const;
            bool operator==(const PlayerState&) const;

        protected:
            const Node* origin;  // we come from this node
            const Node* destination;  // we are moving towards this node

        private:
            Action get_reverse_action() const;
            bool has_reached_destination() const;

        private:
            bool allow_reversing;  // when false, the reverse action is hidden from act, action count, ...
            FPoint pos;  // current position in pixels
        };

    }
}
