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
#include "../Game.h"
#include "../model/GameStateInfo.h"

#include <sstream>
#include <boost/assert.hpp>

namespace PACMAN {
    namespace MODEL {
        class GameState;
    }

    namespace TEST {

        template <class T>
        void assert_equals(T actual_value, T expected_value) {
            if (actual_value == expected_value) {
                return;
            }

            std::ostringstream str;
            str << actual_value << " != " << expected_value;
            BOOST_ASSERT_MSG(false, str.str().c_str());
        }

        class Test {
        public:
            Test();
            int move(int player_index, Direction::Type direction);
            void directions_to_actions(Direction::Type pacman, Direction::Type blinky, Direction::Type pinky, Direction::Type inky, Direction::Type clyde, MODEL::Action* actions, Game& game);

            inline shared_ptr<MODEL::GameState> get_state() {
                return game.get_state();
            }

        private:
            Game game;
            shared_ptr<MODEL::UIHints> uihints;
        };

    }
}
