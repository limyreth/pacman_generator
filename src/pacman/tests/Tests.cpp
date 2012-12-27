/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Tests.h"

#include "../Game.h"
#include "../model/GameState.h"
#include "../Point.h"
#include "../Constants.h"

#include <boost/assert.hpp>

#include <sstream>

// Test
#include "../gui/NullUIHints.h"

namespace PACMAN {

    using namespace MODEL;
    using namespace SPECIFICATION;

    using GUI::NullUIHints;

    namespace TEST {


using std::ostringstream;
using std::cout;
using std::endl;

typedef void (*TestFunc)();

template <class T>
void assert_equals(T actual_value, T expected_value) {
    if (actual_value == expected_value) {
        return;
    }

    ostringstream str;
    str << actual_value << " != " << expected_value;
    BOOST_ASSERT_MSG(false, str.str().c_str());
}


class Test {
public:
    Test() 
    :   uihints(new NullUIHints())
    {
    }

    /*
     * Moves until tile pos changes.
     *
     * Returns steps taken
     */
    int move(int player_index, Direction::Type direction) {
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

    void directions_to_actions(Direction::Type pacman, Direction::Type blinky, Direction::Type pinky, Direction::Type inky, Direction::Type clyde, Action* actions, Game& game) {
        Direction::Type directions[PLAYER_COUNT] = {pacman, blinky, pinky, inky, clyde};
        auto state = game.get_state();
        for (int i=0; i<PLAYER_COUNT; ++i) {
            actions[i] = state->get_player(i).get_action_along_direction(directions[i]);
        }
    }

    shared_ptr<GameState> get_state() {
        return game.get_state();
    }

private:
    Game game;
    shared_ptr<NullUIHints> uihints;
};

void test_initial_game_state() {
    Game game;
    auto state = game.get_state();

    // start positions
    assert_equals(state->get_player(0).get_pixel_pos(), FPoint(14, 23.5) * TILE_SIZE);
    assert_equals(state->get_player(0).get_tile_pos(), IPoint(14, 23));
    assert_equals(state->get_player(GHOST_BLINKY+1).get_pixel_pos(), FPoint(14, 11.5) * TILE_SIZE);
    assert_equals(state->get_player(GHOST_PINKY+1).get_pixel_pos(), FPoint(14, 14) * TILE_SIZE);
    assert_equals(state->get_player(GHOST_INKY+1).get_pixel_pos(), FPoint(12, 14) * TILE_SIZE);
    assert_equals(state->get_player(GHOST_CLYDE+1).get_pixel_pos(), FPoint(16, 14) * TILE_SIZE);

    // vulnerability
    for (int i=0; i < GHOST_COUNT; ++i) {
        BOOST_ASSERT(((GhostState&)state->get_player(i+1)).state == GhostState::NORMAL);
    }
}

void test_ghosts_remain_normal_when_not_eating_energizer() {
    Test test;
    test.move(1, Direction::ANY);
}

void test_pacman_movement_regular_speed_not_cornering() {
    Test test;

    assert_equals(test.move(0, Direction::EAST), (int)ceil((15 - 14) / (FULL_SPEED * NORMAL_PACMAN_SPEED)));

    auto tile_pos = test.get_state()->get_player(0).get_tile_pos();
    assert_equals(tile_pos, IPoint(15, 23));
}


/* TODO
 * move from node to node takes expected amount of ticks:
 * - pacman:
 *   - at regular speed:
 *     - move between nodes
 *     - do a corner
 *   - at vulnerable speed:
 *     - move between nodes
 *     - do a corner
 * - ghost:
 *   - for every speed: move between nodes, =doing a corner
 *
 * fruit, ...
 */

void test(int index) {
    TestFunc tests[] = {
        test_initial_game_state,
        test_ghosts_remain_normal_when_not_eating_energizer,
        test_pacman_movement_regular_speed_not_cornering
    };
    tests[index]();
}

    }
}
