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
#include "model/eat_2_dots.h"
#include "model/eat_energizer.h"
#include "MinimaxTests.h"
#include "GeneratorTests.h"
#include "../util/assertion.h"

using std::string;

namespace PACMAN {
    namespace TEST {

void test(string name) {
    if (name == "MODEL::test_start_foods") MODEL::test_start_foods();
    else if (name == "MODEL::test_initial_game_state") MODEL::test_initial_game_state;
    else if (name == "MODEL::test_ghosts_remain_normal_when_not_eating_energizer") MODEL::test_ghosts_remain_normal_when_not_eating_energizer;
    else if (name == "MODEL::test_pacman_movement_regular_speed_not_cornering") MODEL::test_pacman_movement_regular_speed_not_cornering;
    else if (name == "MODEL::test_dot_eating_no_cornering") MODEL::test_dot_eating_no_cornering;
    else if (name == "MODEL::test_eat_2_dots") MODEL::test_eat_2_dots;
    else if (name == "MODEL::test_eat_energizer") MODEL::test_eat_energizer;
    else if (name == "MinimaxTests::test_1") MinimaxTests::test_1;
    else if (name == "GeneratorTests::test_1") GeneratorTests::test_1;
    else if (name == "GeneratorTests::test_save_load") GeneratorTests::test_save_load;
    else if (name == "GeneratorTests::test_save_load_of_running_instance") GeneratorTests::test_save_load_of_running_instance;
    else ASSERT(false);
}

}}