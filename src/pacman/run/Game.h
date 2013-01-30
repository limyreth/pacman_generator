/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <pacman/model/IntermediateGameState.h>

#include <list>

namespace PACMAN {
    namespace RUN {

        // simplified interface to GameState succession, allowing to move in a certain direction as a certain player
        class Game
        {
        public:
            Game(int player_index);

            bool act(Direction::Type direction, ::PACMAN::MODEL::UIHints& uihints);
            const ::PACMAN::MODEL::GameState& get_state();
            void print_recorded_test(std::ostream&);
            void print_path(std::ostream&);
            int get_steps();
            void reset_steps();

        private:
            int steps;
            const int player_index;
            ::PACMAN::MODEL::IntermediateGameState state;
            std::list< ::PACMAN::MODEL::Action> path;  // actions taken to get to current state
        };

    }
}
