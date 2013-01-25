/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Test.h"

#include "../model/IntermediateGameState.h"
#include "../util/Point.h"
#include "../Constants.h"

using namespace ::PACMAN::MODEL;
using namespace ::PACMAN::SPECIFICATION;

using std::cout;
using std::endl;
using std::vector;

namespace PACMAN {
    namespace TEST {

Test::Test(int player_index)
:   game(player_index),
    player_index(player_index)
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
int Test::move(Direction::Type direction) {
    int steps = 0;

    GameState original = game.get_state();

    auto current = game.get_state();
    while (original.get_player(player_index).get_tile_pos() == current.get_player(player_index).get_tile_pos()) {
        ASSERT(current.food_count == original.food_count);
        ASSERT(current.lives == original.lives);
        ASSERT(current.score == original.score);

        for (int i=0; i < GHOST_COUNT; ++i) {
            ASSERT( ((GhostState&)current.get_player(i+1)).state == ((GhostState&)original.get_player(i+1)).state );
        }

        if (game.act(direction, uihints)) {
            ++steps;
        }
        current = game.get_state();
    }

    return steps;
}

int Test::get_food_count() {
    return get_state()->food_count;
}

const GameState* Test::get_state() {
    return &game.get_state();
}

}}
