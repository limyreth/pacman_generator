/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "Action.h"
#include "../util/Directions.h"
#include "../util/Point.h"

namespace PACMAN {
    namespace MODEL {

        class Node;
        class Nodes;

        class PlayerState : public ASSERTION::Assertable
        {
        public:
            PlayerState();
            PlayerState(const Node* origin, const Node* destination, FPoint pos); // Only for testing
            PlayerState(const Node& initial_node);
            virtual double move(double distance, int player_index) = 0;
            virtual void act(Action action);
            virtual IPoint get_tile_pos() const;
            virtual void print(std::ostream& out, std::string prefix, std::string name) const;
            virtual bool can_reverse() const;
            void reverse();
            bool is_in_tunnel() const;
            bool would_cross_tunnel_edge(double distance, double& d1, double& d2);

            inline FPoint get_pixel_pos() const {
                return pos;
            }

            unsigned char get_action_count() const;

            Action get_action_along_direction(Direction::Type direction) const;

        protected:
            virtual const Nodes& get_nodes() const = 0;
            const FPoint& get_pos() const;
            void invariants() const;
            double move(double distance);
            bool operator==(const PlayerState&) const;

        protected:
            const Node* origin;  // we come from this node
            const Node* destination;  // we are moving towards this node

        private:
            FPoint move_(double distance);
            bool would_cross(double x, FPoint p1, FPoint p2, double distance, double& d1, double& d2);
            Action internal_to_external(Action) const;
            Action external_to_internal(Action) const;
            bool is_reversing_action(Action action) const;
            bool has_reached_destination() const;

        private:
            FPoint pos;  // current position in pixels
        };

    }
}
