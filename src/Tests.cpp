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

namespace PACMAN {
    namespace TEST {

using namespace MODEL;

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
    assert_equals(state->get_player(0).get_pixel_pos(), FPoint(13.5, 23.5) * TILE_SIZE);
    assert_equals(state->get_player(GHOST_BLINKY+1).get_pixel_pos(), FPoint(14, 11.5) * TILE_SIZE);
    assert_equals(state->get_player(GHOST_PINKY+1).get_pixel_pos(), FPoint(14, 14) * TILE_SIZE);
    assert_equals(state->get_player(GHOST_INKY+1).get_pixel_pos(), FPoint(12, 14) * TILE_SIZE);
    assert_equals(state->get_player(GHOST_CLYDE+1).get_pixel_pos(), FPoint(16, 14) * TILE_SIZE);
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

    }
}
