/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "../util/Directions.h"
#include "../model/Game.h"
#include "../model/Action.h"
#include "../model/NullUIHints.h"

namespace PACMAN {
    namespace MODEL {
        class GameState;
    }

    namespace TEST {

        class Test {
        public:
            Test(int player_index);
            int move(Direction::Type direction);
            void directions_to_actions(Direction::Type pacman, Direction::Type blinky, Direction::Type pinky, Direction::Type inky, Direction::Type clyde, MODEL::Action* actions);

            int get_food_count();

            const MODEL::GameState* get_state();

        private:
            int player_index;
            MODEL::Game game;
            MODEL::NullUIHints uihints;
        };

    }
}
