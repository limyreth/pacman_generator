/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "FruitTests.h"
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

/*
 * Spawn 1 fruit, then the second, wait for time out
 */
void FruitTests::test_fruit_timing() {
    std::vector<Action> path = {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 2, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    PathTest test(path);

    // first fruit
    auto state = test.run(501 + 69 +1);  // ct + cc + ct2 + cc + ct + 3 + ct + cc + ct + 3 + ct + cc + ct + 2.5 + ecc + ct2 + cc + ct + 22 + ct + cc + ct2 + ecc + 2.5 + ct + cc + ct + 11 + 69 dots
    ASSERT(!state.is_fruit_spawned());

    state = test.run(502 + 69 +1);
    ASSERT(state.is_fruit_spawned());

    state = test.run(501 + 69 + FRUIT_TICKS +1);
    ASSERT(state.is_fruit_spawned());

    state = test.run(502 + 69 + FRUIT_TICKS +1);
    ASSERT(!state.is_fruit_spawned());

    // second fruit
    state = test.run(1579 + 169 +1);  // ... + 7 + ct + cc + ct + 12 + ct + cc + ct + 15 + ct + cc + ct + 9 + ct + cc + ct2 + cc + ct2 + cc + ct2 + cc + ct2 + cc + ct2 + cc + ct2 + cc + ct2 + cc + ct + 3 + ct + cc + ct2 + cc + ct + 3 + ct + cc + ct2 + cc + ct + 12 + ct + cc + ct + 12 + ct + cc + ct + 2 + ct + cc + ct2 + cc + ct + 2 + ct + cc + ct + 1 + ct + cc + ct + 3 + ct + cc + ct + 1 + ct + cc + ct2 + cc + ct2 + cw + 169 dots
    ASSERT(!state.is_fruit_spawned());

    state = test.run(1580 + 169 +1);
    ASSERT(state.is_fruit_spawned());

    state = test.run(1579 + 169 + FRUIT_TICKS +1);
    ASSERT(state.is_fruit_spawned());

    state = test.run(1580 + 169 + FRUIT_TICKS +1);
    ASSERT(!state.is_fruit_spawned());
}

}}}
