/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "MovementTest.h"
#include <pacman/model/IntermediateGameState.h>
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
        namespace MODEL {

MovementTest::MovementTest(unsigned int player_index)
:   DefaultGameObserver(player_index, shared_ptr<Input>(new DirectionInput(*this))),
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
int MovementTest::move(Direction::Type direction) {
    current_direction = direction;
    original = game.get_state();

    game.run(*this, false, -1);

    return game.get_steps();
}

bool MovementTest::should_stop() {
    return original.get_player(player_index).get_tile_pos() != get_state().get_player(player_index).get_tile_pos();
}

void MovementTest::finished_step(const GameState& current) {
    if (!should_stop()) {
        ASSERT(current.get_food_count() == original.get_food_count());
        ASSERT(current.get_lives() == original.get_lives());
        ASSERT(current.get_score() == original.get_score());
    }
}

const GameState& MovementTest::get_state() {
    return game.get_state();
}

Direction::Type MovementTest::get_preferred_direction() {
    return current_direction;
}

}}}
