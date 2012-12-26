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

    using GUI::NullUIHints;

    namespace TEST {


using std::ostringstream;
using std::cout;
using std::endl;

typedef void (*TestFunc)();

template <class T>
void assert_equals(T a, T b) {
    if (a == b) {
        return;
    }

    ostringstream str;
    str << a << " != " << b;
    BOOST_ASSERT_MSG(false, str.str().c_str());
}


class Test {
public:
    Test() 
    :   uihints(new NullUIHints())
    {
    }

    shared_ptr<GameState> move(int player_index, Direction::Type direction, int steps) {
        auto original = game.get_state();
        auto current = original;

        Action actions[PLAYER_COUNT] = {0, 0, 0, 0, 0};
        actions[player_index] = original->get_player(player_index).get_action_along_direction(direction);

        for (int i=0; i<steps; ++i) {
            assert_equals(original->food_count, current->food_count);
            assert_equals(original->lives, current->lives);
            assert_equals(original->score, current->score);

            game.step(actions, uihints);
            current = game.get_state();
        }
    }

    void directions_to_actions(Direction::Type pacman, Direction::Type blinky, Direction::Type pinky, Direction::Type inky, Direction::Type clyde, Action* actions, Game& game) {
        Direction::Type directions[PLAYER_COUNT] = {pacman, blinky, pinky, inky, clyde};
        auto state = game.get_state();
        for (int i=0; i<PLAYER_COUNT; ++i) {
            actions[i] = state->get_player(i).get_action_along_direction(directions[i]);
        }
    }

private:
    Game game;
    shared_ptr<NullUIHints> uihints;
};

void test_1() {
    Game game;
    auto state = game.get_state();
    assert_equals(state->get_player(0).get_pixel_pos(), FPoint(13.5, 23.5) * TILE_SIZE);
    assert_equals(state->get_player(GHOST_BLINKY+1).get_pixel_pos(), FPoint(14, 11.5) * TILE_SIZE);
    assert_equals(state->get_player(GHOST_PINKY+1).get_pixel_pos(), FPoint(14, 14) * TILE_SIZE);
    assert_equals(state->get_player(GHOST_INKY+1).get_pixel_pos(), FPoint(12, 14) * TILE_SIZE);
    assert_equals(state->get_player(GHOST_CLYDE+1).get_pixel_pos(), FPoint(16, 14) * TILE_SIZE);
}

void test_2() {
    // pacman movement between 2 regular nodes
    //Test test;
    //test.move(0, Direction::EAST, (int)ceil((14 - 13.5) / NORMAL_PACMAN_SPEED))
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
        test_1,
        test_2
    };
    tests[index]();
}

    }
}
