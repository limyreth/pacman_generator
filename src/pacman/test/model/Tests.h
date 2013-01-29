/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <memory>

namespace PACMAN {
    namespace TEST {
        namespace MODEL {

            void test_start_foods();
            void test_initial_game_state();
            void test_ghosts_remain_normal_when_not_eating_energizer();
            void test_pacman_movement_regular_speed_not_cornering();
            void test_dot_eating_no_cornering();
            void test_eat_1_ghost();
            void test_eat_2_ghosts();
            void test_eat_3_ghosts();
            void test_eat_2_dots();
            void test_eat_energizer();
            void test_eat_fruit();
            void test_eat_fruit_ghost();

        }
    }
}
