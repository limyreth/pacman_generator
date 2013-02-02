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
            void test_pacman_movement_regular_speed_cornering();
            void test_dot_eating_no_cornering();
            void test_eat_1_ghost();
            void test_eat_2_ghosts();
            void test_eat_3_ghosts();
            void test_eat_4_ghosts();
            void test_eat_ghost_energizer_ghost();
            void test_eat_2_dots();
            void test_eat_energizer();
            void test_eat_fruit();
            void test_eat_fruit_ghost();
            void test_blinky_respawn();
            void test_pinky_respawn();
            void test_inky_respawn();
            void test_clyde_respawn();
            void test_eat_energizer_while_leaving_ghost_in_pen();
            void test_dead_ghost_tunnel_speed();

        }
    }
}
