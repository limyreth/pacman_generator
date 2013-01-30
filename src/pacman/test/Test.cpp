/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Test.h"
#include <pacman/model/IntermediateGameState.h>
#include <pacman/model/NullUIHints.h>
#include <pacman/util/Point.h>
#include <pacman/Constants.h>
#include <pacman/run/DirectionInput.h>

using namespace ::PACMAN::RUN;
using namespace ::PACMAN::MODEL;
using namespace ::PACMAN::SPECIFICATION;

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;

namespace PACMAN {
    namespace TEST {

Test::Test(int player_index)
:   player_index(player_index)
{
    game.init(Game::make_inputs(player_index, shared_ptr<Input>(new DirectionInput(*this))), shared_ptr<UIHints>(new NullUIHints));
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
    current_direction = direction;
    original = game.get_state();

    game.reset_steps();
    game.run(*this, false);

    return game.get_steps();
}

bool Test::should_stop() {
    return original.get_player(player_index).get_tile_pos() != get_state().get_player(player_index).get_tile_pos();
}

void Test::finished_step(const GameState& current) {
    if (!should_stop()) {
        ASSERT(current.food_count == original.food_count);
        ASSERT(current.lives == original.lives);
        ASSERT(current.score == original.score);

        for (int i=0; i < GHOST_COUNT; ++i) {
            ASSERT( ((GhostState&)current.get_player(i+1)).state == ((GhostState&)original.get_player(i+1)).state );
        }
    }
}

bool Test::is_paused() {
    return false;
}

void Test::pause() {
    REQUIRE(false);
}

const GameState& Test::get_state() {
    return game.get_state();
}

Direction::Type Test::get_preferred_direction() {
    return current_direction;
}

}}
