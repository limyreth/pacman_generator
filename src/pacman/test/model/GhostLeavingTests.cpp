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

}}}
