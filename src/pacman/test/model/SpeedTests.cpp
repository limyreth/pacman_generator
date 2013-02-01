/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "SpeedTests.h"
#include <pacman/model/GameState.h>
#include <pacman/model/GhostState.h>
#include <pacman/test/model/PathTest.h>

using std::cout;
using std::endl;
using std::vector;

using namespace ::PACMAN::MODEL;
using namespace ::PACMAN::SPECIFICATION;

namespace PACMAN {
    namespace TEST {
        namespace MODEL {

/*
 * Normal ghost speed as pacman approaches the energizer
 * Vulnerable ghost speed as soon pacman as pacman eats the energizer
 * Dead ghost speed when ghost is eaten
 */
void SpeedTests::test_dead_ghost() {
    std::vector<Action> path = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
    PathTest test(path);

    // blinky moved to next tile at normal ghost speed
    auto state = test.run(8 +1);
    ASSERT(state.get_player(GHOST_BLINKY+1).get_tile_pos() == IPoint(13, 11));

    state = test.run(9 +1);
    ASSERT(state.get_player(GHOST_BLINKY+1).get_tile_pos() == IPoint(12, 11));

    // pacman eats energizer: 317 +1 = (ct + cc + ct2 + cc + ct2 + cc + ct + 6 + ct + cc + ct + 3 + ct + cc + ct2 + cc + ct2 + cc + ct2 + cc + ct2 + cc + ct + 1 + ct + cc + ct + 2 + ct + cc + ct) / ns + 27 dots
    // blinky has travelled ~37.64 tiles, will reach the next tile after a distance of ~0.356, i.e. in 5 ticks
    state = test.run(317 +1);
    ASSERT(state.get_vulnerable_ghost_count() == 0);
    state = test.run(318 +1);
    ASSERT(state.get_vulnerable_ghost_count() == 2);

    // blinky nearly moved to next tile at vulnerable ghost speed
    state = test.run(321 +1);
    ASSERT(state.get_player(GHOST_BLINKY+1).get_tile_pos() == IPoint(6, 5));

    // blinky moved to next tile
    state = test.run(322 +1); 
    ASSERT(state.get_player(GHOST_BLINKY+1).get_tile_pos() == IPoint(6, 4));

    // pacman nearly eats Pinky
    state = test.run(377 +1);  // (ct + cc + ct2 + cc + ct2 + cc + ct + 6 + ct + cc + ct + 3 + ct + cc + ct2 + cc + ct2 + cc + ct2 + cc + ct2 + cc + ct + 1 + ct + cc + ct + 2 + ct + cc + ct) / ns + (1 + ct + cc + ct + 2 + ct + cc + ct) / es + 33 dots + 1 energizer
    ASSERT(((GhostState&)state.get_player(GHOST_PINKY+1)).state == GhostState::VULNERABLE);

    // pacman eats Pinky
    // Pinky moved 42.47 tiles, will return to previous tile after a distance of ~0.97, in 4 ticks
    state = test.run(378 +1);
    ASSERT(((GhostState&)state.get_player(GHOST_PINKY+1)).state == GhostState::DEAD);

    // pinky nearly moved to next tile at dead ghost speed
    state = test.run(381 +1);
    ASSERT(state.get_player(GHOST_PINKY+1).get_tile_pos() == IPoint(6, 3));

    // pinky moved to next tile at dead ghost speed
    state = test.run(382 +1);
    ASSERT(state.get_player(GHOST_PINKY+1).get_tile_pos() == IPoint(6, 4));
}

}}}
