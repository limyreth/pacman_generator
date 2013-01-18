/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Test.h"

#include "util.h"

#include "../model/GameState.h"
#include "../Point.h"
#include "../Constants.h"

using namespace ::PACMAN::MODEL;
using namespace ::PACMAN::SPECIFICATION;

using ::PACMAN::GUI::NullUIHints;

using std::cout;
using std::endl;
using std::vector;

namespace PACMAN {
    namespace TEST {

Test::Test() 
:   state(GameState::new_game()),
    is_initial(true)
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
    int steps = 0;
    vector<Action> actions(PLAYER_COUNT, 0);

    if (is_initial) {
        is_initial = false;

        auto& player = state.get_player(player_index);
        if (player.get_legal_actions().count > 0) {
            actions.at(player_index) = player.get_action_along_direction(direction);
        }
        state.act(actions, state, uihints);
    }

    GameState original = state;

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

        auto new_state = GameState(state, uihints);
        auto& player = new_state.get_player(player_index);
        if (player.get_legal_actions().count > 0) {
            actions.at(player_index) = player.get_action_along_direction(direction);
        }
        new_state.act(actions, state, uihints);
        state = new_state;

        ++steps;
        cout << steps << endl;
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

}}
