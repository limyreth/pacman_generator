/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Tests.h"
#include "model/Tests.h"
#include "model/NodesTests.h"
#include "model/SpeedTests.h"
#include "model/VulnerabilityTests.h"
#include "model/FruitTests.h"
#include "model/GhostLeavingTests.h"
#include "MinimaxTests.h"
#include "GeneratorTests.h"
#include "../util/assertion.h"

using std::string;

namespace PACMAN {
    namespace TEST {

void test(string name) {
    if (name == "MODEL::test_start_foods") MODEL::test_start_foods();
    else if (name == "MODEL::NodesTests::test_pacman_nodes") MODEL::NodesTests::test_pacman_nodes();
    else if (name == "MODEL::NodesTests::test_ghost_nodes") MODEL::NodesTests::test_ghost_nodes();
    else if (name == "MODEL::test_initial_game_state") MODEL::test_initial_game_state();
    else if (name == "MODEL::test_ghosts_remain_normal_when_not_eating_energizer") MODEL::test_ghosts_remain_normal_when_not_eating_energizer();
    else if (name == "MODEL::test_pacman_movement_regular_speed_not_cornering") MODEL::test_pacman_movement_regular_speed_not_cornering();
    else if (name == "MODEL::test_pacman_movement_regular_speed_cornering") MODEL::test_pacman_movement_regular_speed_cornering();
    else if (name == "MODEL::test_dot_eating_no_cornering") MODEL::test_dot_eating_no_cornering();
    else if (name == "MODEL::test_eat_2_dots") MODEL::test_eat_2_dots();
    else if (name == "MODEL::test_eat_energizer") MODEL::test_eat_energizer();
    else if (name == "MODEL::test_eat_fruit") MODEL::test_eat_fruit();
    else if (name == "MODEL::test_eat_fruit_ghost") MODEL::test_eat_fruit_ghost();
    else if (name == "MODEL::test_eat_1_ghost") MODEL::test_eat_1_ghost();
    else if (name == "MODEL::test_eat_2_ghosts") MODEL::test_eat_2_ghosts();
    else if (name == "MODEL::test_eat_3_ghosts") MODEL::test_eat_3_ghosts();
    else if (name == "MODEL::test_eat_4_ghosts") MODEL::test_eat_4_ghosts();
    else if (name == "MODEL::test_eat_ghost_energizer_ghost") MODEL::test_eat_ghost_energizer_ghost();
    else if (name == "MODEL::test_blinky_respawn") MODEL::test_blinky_respawn();
    else if (name == "MODEL::test_pinky_respawn") MODEL::test_pinky_respawn();
    else if (name == "MODEL::test_inky_respawn") MODEL::test_inky_respawn();
    else if (name == "MODEL::test_clyde_respawn") MODEL::test_clyde_respawn();
    else if (name == "MODEL::test_eat_energizer_while_leaving_ghost_in_pen") MODEL::test_eat_energizer_while_leaving_ghost_in_pen();
    else if (name == "MODEL::test_dead_ghost_tunnel_speed") MODEL::test_dead_ghost_tunnel_speed();
    else if (name == "MODEL::test_pacman_dies") MODEL::test_pacman_dies();
    else if (name == "MODEL::test_pacman_wins") MODEL::test_pacman_wins();
    else if (name == "MODEL::SpeedTests::test_dead_ghost") MODEL::SpeedTests::test_dead_ghost();
    else if (name == "MODEL::SpeedTests::test_tunnel_ghost") MODEL::SpeedTests::test_tunnel_ghost();
    else if (name == "MODEL::SpeedTests::test_elroy") MODEL::SpeedTests::test_elroy();
    else if (name == "MODEL::VulnerabilityTests::test_energizer_time") MODEL::VulnerabilityTests::test_energizer_time();
    else if (name == "MODEL::VulnerabilityTests::test_2_energizers_time") MODEL::VulnerabilityTests::test_2_energizers_time();
    else if (name == "MODEL::GhostLeavingTests::test_blinky_pinky_immediately_leave") MODEL::GhostLeavingTests::test_blinky_pinky_immediately_leave();
    else if (name == "MODEL::GhostLeavingTests::test_dots_eaten") MODEL::GhostLeavingTests::test_dots_eaten();
    else if (name == "MODEL::GhostLeavingTests::test_time") MODEL::GhostLeavingTests::test_time();
    else if (name == "MODEL::FruitTests::test_fruit_timing") MODEL::FruitTests::test_fruit_timing();
    else if (name == "MinimaxTests::test_1") MinimaxTests::test_1();
    else if (name == "GeneratorTests::test_1") GeneratorTests::test_1();
    else if (name == "GeneratorTests::test_save_load") GeneratorTests::test_save_load();
    else if (name == "GeneratorTests::test_save_load_of_running_instance") GeneratorTests::test_save_load_of_running_instance();
    else ASSERT(false);
}

}}
