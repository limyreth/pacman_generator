/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Tests.h"

#include "Game.h"
#include "GameState.h"
#include "Point.h"
#include "Constants.h"

#include <boost/assert.hpp>

#include <sstream>

using std::ostringstream;
using std::cout;
using std::endl;

typedef void (*Test)();

template <class T>
void assert_equals(T a, T b) {
    if (a == b) {
        return;
    }

    ostringstream str;
    str << a << " != " << b;
    BOOST_ASSERT_MSG(false, str.str().c_str());

}

void test_1() {
    Game game;
    auto state = game.get_state();
    assert_equals(state->get_pacman_state().get_pixel_pos(), FPoint(13.5, 23.5) * TILE_SIZE);
    assert_equals(state->get_ghost_state(GHOST_BLINKY).get_pixel_pos(), FPoint(14, 11.5) * TILE_SIZE);
    assert_equals(state->get_ghost_state(GHOST_PINKY).get_pixel_pos(), FPoint(14, 14) * TILE_SIZE);
    assert_equals(state->get_ghost_state(GHOST_INKY).get_pixel_pos(), FPoint(12, 14) * TILE_SIZE);
    assert_equals(state->get_ghost_state(GHOST_CLYDE).get_pixel_pos(), FPoint(16, 14) * TILE_SIZE);
}

void test_2() {
    throw 1;
}

void test(int index) {
    Test tests[] = {
        test_1,
        test_2
    };
    tests[index]();
}
