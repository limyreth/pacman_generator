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
    ASSERT(state.get_vulnerable_ghost_count() == 4);

    // blinky nearly moved to next tile at vulnerable ghost speed
    state = test.run(321 +1);
    ASSERT(state.get_player(GHOST_BLINKY+1).get_tile_pos() == IPoint(6, 5));

    // blinky moved to next tile
    state = test.run(322 +1); 
    ASSERT(state.get_player(GHOST_BLINKY+1).get_tile_pos() == IPoint(6, 4));

    // pacman nearly eats Pinky
    state = test.run(377 +1);  // (ct + cc + ct2 + cc + ct2 + cc + ct + 6 + ct + cc + ct + 3 + ct + cc + ct2 + cc + ct2 + cc + ct2 + cc + ct2 + cc + ct + 1 + ct + cc + ct + 2 + ct + cc + ct) / ns + (1 + ct + cc + ct + 2 + ct + cc + ct) / es + 33 dots + 1 energizer
    ASSERT(((GhostState&)state.get_player(GHOST_PINKY+1)).is_vulnerable());

    // pacman eats Pinky
    // Pinky moved 42.47 tiles, will return to previous tile after a distance of ~0.97, in 4 ticks
    state = test.run(378 +1);
    ASSERT(((GhostState&)state.get_player(GHOST_PINKY+1)).is_dead());

    // pinky nearly moved to next tile at dead ghost speed
    state = test.run(381 +1);
    ASSERT(state.get_player(GHOST_PINKY+1).get_tile_pos() == IPoint(6, 3));

    // pinky moved to next tile at dead ghost speed
    state = test.run(382 +1);
    ASSERT(state.get_player(GHOST_PINKY+1).get_tile_pos() == IPoint(6, 4));
}

void SpeedTests::test_tunnel_ghost() {
    std::vector<Action> path = {1, 1, 1, 0, 1, 2, 2};
    PathTest test(GHOST_BLINKY+1, path);

    // nearly moved up to start of tunnel at normal speed
    auto state = test.run(117 +1);
    ASSERT(state.get_player(GHOST_BLINKY+1).get_tile_pos() == IPoint(6, 14));

    // moved up to start of tunnel at normal speed
    state = test.run(118 +1);  // 14 tiles
    ASSERT(state.get_player(GHOST_BLINKY+1).get_tile_pos() == IPoint(5, 14));

    // nearly moved to other end of tunnel at tunnel speed
    state = test.run(307 +1);
    ASSERT(state.get_player(GHOST_BLINKY+1).get_tile_pos() == IPoint(22, 14));

    // moved to other end of tunnel at tunnel speed
    state = test.run(308 +1);  // + 12 tiles
    ASSERT(state.get_player(GHOST_BLINKY+1).get_tile_pos() == IPoint(21, 14));

    // nearly moved to next tile at normal speed again
    state = test.run(315 +1);
    ASSERT(state.get_player(GHOST_BLINKY+1).get_tile_pos() == IPoint(21, 14));

    // moved to next tile at normal speed again
    state = test.run(316
            +1  // allowed inaccuracy caused by entering/exiting tunnel
            +1);  // + 1 tiles
    ASSERT(state.get_player(GHOST_BLINKY+1).get_tile_pos() == IPoint(20, 14));
}

/*
 * Elroy1 and 2 speeds
 */
void SpeedTests::test_elroy() {
    std::vector<Action> path = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1};
    PathTest test(path);

    // blinky becomes elroy1 at 20 food left: 2519 (value determined by recording when food count reaches 10 + recording where ghosts are)

    // elroy1 speed
    auto state = test.run(2519);
    auto p1 = state.get_player(GHOST_BLINKY+1).get_pixel_pos();
    state = test.run(2519 + 1);
    auto p2 = state.get_player(GHOST_BLINKY+1).get_pixel_pos();
    ASSERT((p2 - p1).length() - FULL_SPEED * ELROY1_SPEED < MAX_ROUNDING_ERROR);

    // elroy1 becomes elroy2 at 10 food left: 2690
    state = test.run(2690);
    p1 = state.get_player(GHOST_BLINKY+1).get_pixel_pos();
    auto pinky1 = state.get_player(GHOST_PINKY+1).get_pixel_pos();
    state = test.run(2690 + 1);
    p2 = state.get_player(GHOST_BLINKY+1).get_pixel_pos();
    auto pinky2 = state.get_player(GHOST_PINKY+1).get_pixel_pos();
    ASSERT((p2 - p1).length() - FULL_SPEED * ELROY2_SPEED < MAX_ROUNDING_ERROR);
    ASSERT((pinky2 - pinky1).length() - FULL_SPEED * GHOST_NORMAL_SPEED < MAX_ROUNDING_ERROR);

    // ghosts become vulnerable
    state = test.run(2962);
    p1 = state.get_player(GHOST_BLINKY+1).get_pixel_pos();
    state = test.run(2962 + 1);
    p2 = state.get_player(GHOST_BLINKY+1).get_pixel_pos();
    ASSERT((p2 - p1).length() - FULL_SPEED * GHOST_VULNERABLE_SPEED < MAX_ROUNDING_ERROR);
}

}}}
