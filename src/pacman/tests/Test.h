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
#include "../model/GameStateInfo.h"
#include "../gui/NullUIHints.h"
#include "../Utility.h"

#include <sstream>
#include <boost/assert.hpp>

namespace PACMAN {
    namespace MODEL {
        class GameState;
    }

    namespace TEST {

#define assert_equals(actual_value, expected_value) BOOST_ASSERT_MSG(actual_value == expected_value, (to_string(actual_value) + " != " + to_string(expected_value)).c_str());

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
        };

    }
}
