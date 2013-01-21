/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "IntermediateGameState.h"
#include "../util/serialization.h"
#include "../util/assertion.h"
#include "../model/PacmanNodes.h"
#include "../model/GhostNodes.h"

using std::vector;
using std::cout;
using std::endl;

namespace PACMAN {
    namespace MODEL {

// intermediate state with new_game as predecessor
IntermediateGameState::IntermediateGameState(const GameState predecessor)
:   predecessor(predecessor),
    successor(predecessor)
{
    for (int i=0; i < PLAYER_COUNT; ++i) {
        movement_excess[i] = 0.0;
    }
}

IntermediateGameState::IntermediateGameState(const GameState predecessor, UIHints& uihints)
:   predecessor(predecessor),
    successor(GameState(predecessor, uihints, movement_excess))
{
}

IntermediateGameState IntermediateGameState::new_game() {
    return IntermediateGameState(GameState(PACMAN_NODES.get_spawn(), GHOST_NODES.get_spawns()));
}

const PlayerState& IntermediateGameState::get_player(int index) const {
    return successor.get_player(index);
}

bool IntermediateGameState::operator==(const IntermediateGameState& o) const {
    for (int i=0; i < PLAYER_COUNT; ++i) {
        if (o.movement_excess[i] != movement_excess[i]) {
            return false;
        }
    }

    return o.predecessor == predecessor &&
        o.successor == successor;
}

IntermediateGameState IntermediateGameState::act(const std::vector<Action>& actions, UIHints& uihints) const {
    auto copy = successor;
    copy.act(actions, predecessor, uihints, movement_excess);

    IntermediateGameState next_intermediate(copy, uihints);
    return next_intermediate;
}

unsigned char IntermediateGameState::get_action_count(int player_index) const {
    return get_player(player_index).get_action_count();
}

Action IntermediateGameState::get_action_along_direction(int player_index, Direction::Type direction) const {
    return get_player(player_index).get_action_along_direction(direction);
}

}}
