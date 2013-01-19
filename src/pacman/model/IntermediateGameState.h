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

        class UIHints;
        class GameState;
        class PlayerState;

        // Each GameState shows the state at the begin/end of a tick
        class IntermediateGameState
        {
        public:
            IntermediateGameState(const GameState predecessor, UIHints&);
            IntermediateGameState(std::istream& in, UIHints&);

            static IntermediateGameState new_game();

            void save(std::ostream& out) const;
            IntermediateGameState act(const std::vector<Action>& actions, UIHints&) const;
            bool operator==(const IntermediateGameState&) const;
            bool operator!=(const IntermediateGameState& o) const {
                return !(o == *this);
            }

            const PlayerState& get_player(int index) const;

            inline const GameState& get_predecessor() const {
                return predecessor;
            }

        private:
            IntermediateGameState(const GameState predecessor);

        private:
            GameState predecessor;
            GameState successor;
            double movement_excess[PLAYER_COUNT];
        };

    }
}