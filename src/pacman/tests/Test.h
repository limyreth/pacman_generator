/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "../Directions.h"
#include "../model/GameState.h"
#include "../model/Action.h"
#include "../gui/NullUIHints.h"

namespace PACMAN {
    namespace MODEL {
        class GameState;
    }

    namespace TEST {

        class Test {
        public:
            Test();
            int move(int player_index, Direction::Type direction);
            void directions_to_actions(Direction::Type pacman, Direction::Type blinky, Direction::Type pinky, Direction::Type inky, Direction::Type clyde, MODEL::Action* actions);

            int get_food_count();

            inline MODEL::GameState* get_state() {
                return &state;
            }

        private:
            MODEL::GameState state;
            GUI::NullUIHints uihints;
            bool is_initial;
        };

    }
}
