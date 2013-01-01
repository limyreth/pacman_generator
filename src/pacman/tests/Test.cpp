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
#include "../model/PacmanNodes.h"
#include "../model/GhostNodes.h"
#include "../Point.h"
#include "../Constants.h"

namespace PACMAN {

    using namespace MODEL;
    using namespace SPECIFICATION;

    using GUI::NullUIHints;

    namespace TEST {


using std::cout;
using std::endl;

Test::Test() 
:   state(PACMAN_NODES.get_spawn(), GHOST_NODES.get_spawns())
{
}

/*
 * Moves until tile pos changes.
 *
 * Note that player might not currently move in direction, but the player is
 * allowed to change direction during this movement, then it will try to change
 * to that direction.
 *
 * Returns steps taken
 */
int Test::move(int player_index, Direction::Type direction) {
    GameState original = state;
    auto current = original;
    int steps = 0;

    Action actions[PLAYER_COUNT] = {0, 0, 0, 0, 0};
    actions[player_index] = original.get_player(player_index).get_action_along_direction(direction);

    while (original.get_player(player_index).get_tile_pos() == state.get_player(player_index).get_tile_pos()) {
        assert_equals(state.food_count, original.food_count);
        assert_equals(state.lives, original.lives);
        assert_equals(state.score, original.score);

        for (int i=0; i < GHOST_COUNT; ++i) {
            assert_equals(
                ((GhostState&)state.get_player(i+1)).state,
                ((GhostState&)original.get_player(i+1)).state
            );
        }

        state = GameState(actions, &state, uihints);

        ++steps;
    }

    return steps;
}

void Test::directions_to_actions(Direction::Type pacman, Direction::Type blinky, Direction::Type pinky, Direction::Type inky, Direction::Type clyde, Action* actions) {
    Direction::Type directions[PLAYER_COUNT] = {pacman, blinky, pinky, inky, clyde};
    for (int i=0; i<PLAYER_COUNT; ++i) {
        actions[i] = state.get_player(i).get_action_along_direction(directions[i]);
    }
}

int Test::get_food_count() {
    return get_state()->food_count;
}

    }
}
