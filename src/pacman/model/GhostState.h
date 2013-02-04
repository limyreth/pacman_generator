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
                NORMAL = 0,
                DEAD = 2,
                WAITING = 3,  // when in ghost pen, but not yet allowed to leave
            };

        public:
            GhostState();
            GhostState(const int origin_id, const int destination_id, FPoint pos, State state, bool vulnerable); // Only for testing
            GhostState(const Node& initial_node);

            float move(float distance, int player_index);
            void act(Action action);
            bool can_reverse() const;
            void print(std::ostream& out, std::string prefix, std::string name) const;

            void die();
            void leave_pen();
            bool become_invulnerable();
            bool try_become_vulnerable();
            bool is_vulnerable() const;
            bool is_dead() const;
            bool is_waiting() const;

            bool operator==(const GhostState&) const;
            bool operator!=(const GhostState& o) const {
                return !(*this == o);
            }

        protected:
            virtual const Nodes& get_nodes() const;
            void invariants() const;

        private:
            bool is_leaving_pen() const;

        private:
            State state;
            bool vulnerable;
        };

    }
}
