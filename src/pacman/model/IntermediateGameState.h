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
#include "GameState.h"
#include "../Constants.h"

namespace PACMAN {
    namespace MODEL {

        class GameStateObserver;
        class GameState;
        class PlayerState;

        // Each GameState shows the state at the begin/end of a tick
        class IntermediateGameState
        {
        public:
            static IntermediateGameState new_game();

            IntermediateGameState act(const std::vector<Action>& actions, GameStateObserver&) const;
            unsigned int get_action_count(int player_index) const;
            Action get_action_along_direction(int player_index, Direction::Type direction) const;

            bool operator==(const IntermediateGameState&) const;
            bool operator!=(const IntermediateGameState& o) const {
                return !(o == *this);
            }

            inline const GameState& get_predecessor() const {
                return predecessor;
            }

        private:
            IntermediateGameState(const GameState predecessor);

        private:
            GameState predecessor;
            GameState successor;
            float movement_excess[PLAYER_COUNT];
            bool suppress_action;

            enum State {
                REVERSE_ALL_CHOICE,  // after time progression, each player decides whether or not to reverse
                ABOUT_TO_ACT,  // each player chooses where to move to, if any
                REVERSE_PACMAN_CHOICE,  // after acting, pacman decides whether or not to reverse
                GAME_OVER
            } state;
        };

    }
}
