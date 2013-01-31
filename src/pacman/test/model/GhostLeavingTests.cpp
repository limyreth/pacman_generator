/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "GhostLeavingTests.h"
#include <pacman/model/GameState.h>
#include <pacman/test/model/PathTest.h>

using std::cout;
using std::endl;
using std::vector;

using namespace ::PACMAN::MODEL;
using namespace ::PACMAN::SPECIFICATION;

namespace PACMAN {
    namespace TEST {
        namespace MODEL {

void GhostLeavingTests::test_blinky_pinky_immediately_leave() {
    std::vector<Action> path = {0, 1};
    PathTest test(path);

    auto original = test.run(1);
    auto state = test.run(1 +1);
    ASSERT(original.get_player(GHOST_BLINKY+1).get_pixel_pos() != state.get_player(GHOST_BLINKY+1).get_pixel_pos());  // blinky moved
    ASSERT(original.get_player(GHOST_PINKY+1).get_pixel_pos() != state.get_player(GHOST_PINKY+1).get_pixel_pos());
}

/*
 * Leaving due to dots being eaten
 */
void GhostLeavingTests::test_dots_eaten() {
    std::vector<Action> path = {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0};
    PathTest test(path);

    // inky at 30 dots
    {
        auto state1 = test.run(230 +1);
        auto state2 = test.run(231 +1);  // ct + cc + ct2 + cc + ct + 3 + ct + cc + ct + 3 + ct + cc + ct + 2.5 + ecc + ct2 + cc + ct + 4 + 29 dots
        ASSERT(state1.get_player(GHOST_INKY+1).get_pixel_pos() == state2.get_player(GHOST_INKY+1).get_pixel_pos());  // inky not moving yet

        auto state3 = test.run(232 +1);
        ASSERT(state2.get_player(GHOST_INKY+1).get_pixel_pos() != state3.get_player(GHOST_INKY+1).get_pixel_pos());
    }

    // clyde at 90 dots
    {
        auto state1 = test.run(741 +1);
        auto state2 = test.run(742 +1);  // ct + cc + ct2 + cc + ct + 3 + ct + cc + ct + 3 + ct + cc + ct + 2.5 + ecc + ct2 + cc + ct + 22 + ct + cc + ct2 + ecc + 2.5 + ct + cc + ct + 18 + ct + cc + ct + 10 + 89 dots
        ASSERT(state1.get_player(GHOST_CLYDE+1).get_pixel_pos() == state2.get_player(GHOST_CLYDE+1).get_pixel_pos());  // inky not moving yet

        auto state3 = test.run(743 +1);
        ASSERT(state2.get_player(GHOST_CLYDE+1).get_pixel_pos() != state3.get_player(GHOST_CLYDE+1).get_pixel_pos());
    }

}

}}}
