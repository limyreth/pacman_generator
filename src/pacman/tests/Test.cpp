/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Test.h"

#include "../model/GameState.h"
#include "../Point.h"
#include "../Constants.h"
#include "../gui/NullUIHints.h"

namespace PACMAN {

    using namespace MODEL;
    using namespace SPECIFICATION;

    using GUI::NullUIHints;

    namespace TEST {


using std::cout;
using std::endl;

Test::Test() 
:   uihints(new NullUIHints())
{
}

/*
 * Moves until tile pos changes.
 *
 * Returns steps taken
 */
int Test::move(int player_index, Direction::Type direction) {
    auto original = game.get_state();
    auto current = original;
    int steps = 0;

    Action actions[PLAYER_COUNT] = {0, 0, 0, 0, 0};
    actions[player_index] = original->get_player(player_index).get_action_along_direction(direction);

    while (original->get_player(player_index).get_tile_pos() == current->get_player(player_index).get_tile_pos()) {
        assert_equals(current->food_count, original->food_count);
        assert_equals(current->lives, original->lives);
        assert_equals(current->score, original->score);

        for (int i=0; i < GHOST_COUNT; ++i) {
            assert_equals(
                ((GhostState&)current->get_player(i+1)).state,
                ((GhostState&)original->get_player(i+1)).state
            );
        }

        game.step(actions, uihints);
        current = game.get_state();
        ++steps;
    }

    return steps;
}

void Test::directions_to_actions(Direction::Type pacman, Direction::Type blinky, Direction::Type pinky, Direction::Type inky, Direction::Type clyde, Action* actions, Game& game) {
    Direction::Type directions[PLAYER_COUNT] = {pacman, blinky, pinky, inky, clyde};
    auto state = game.get_state();
    for (int i=0; i<PLAYER_COUNT; ++i) {
        actions[i] = state->get_player(i).get_action_along_direction(directions[i]);
    }
}

    }
}
