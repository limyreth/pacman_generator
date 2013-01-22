/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "IntermediateGameState.h"

namespace PACMAN {
    namespace MODEL {

        // simplified interface to GameState succession, allowing to move in a certain direction as a certain player
        class Game
        {
        public:
            Game(int player_index);

            bool act(Direction::Type direction, UIHints& uihints);
            const MODEL::GameState& get_state();

        private:
            MODEL::GameState current;
            int player_index;
            MODEL::IntermediateGameState state;
        };

    }
}
