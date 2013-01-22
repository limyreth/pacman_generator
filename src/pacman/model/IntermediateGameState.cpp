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
#include "../Constants.h"

using std::vector;
using std::cout;
using std::endl;

namespace PACMAN {
    namespace MODEL {

// intermediate state with new_game as predecessor
IntermediateGameState::IntermediateGameState(const GameState predecessor)
:   predecessor(predecessor),
    successor(predecessor),
    state(ABOUT_TO_ACT),
    suppress_action(false)
{
    for (int i=0; i < PLAYER_COUNT; ++i) {
        movement_excess[i] = 0.0;
    }
}

IntermediateGameState IntermediateGameState::new_game() {
    return IntermediateGameState(GameState(PACMAN_NODES.get_spawn(), GHOST_NODES.get_spawns()));
}

bool IntermediateGameState::operator==(const IntermediateGameState& o) const {
    for (int i=0; i < PLAYER_COUNT; ++i) {
        if (o.movement_excess[i] != movement_excess[i]) {
            return false;
        }
    }

    return o.predecessor == predecessor &&
        o.successor == successor &&
        o.state == state;
}

IntermediateGameState IntermediateGameState::act(const std::vector<Action>& actions, UIHints& uihints) const {
    auto copy = *this;

    if (state == REVERSE_ALL_CHOICE) {
        if (!suppress_action) {
            for (int player_index = 0; player_index < PLAYER_COUNT; ++player_index) {
                if (actions.at(player_index) == 0) {
                    copy.successor.get_player(player_index).reverse();
                } else {
                    REQUIRE(actions.at(player_index) == 1);
                }
            }
        }

        copy.successor.initial_movement(copy.predecessor, uihints, copy.movement_excess);
        copy.suppress_action = false;
        copy.state = ABOUT_TO_ACT;
    }
    else if (state == ABOUT_TO_ACT) {
        ASSERT(!suppress_action);
        copy.suppress_action = !copy.successor.act(actions, predecessor, uihints, movement_excess);
        copy.state = REVERSE_PACMAN_CHOICE;
    }
    else if (state == REVERSE_PACMAN_CHOICE) {
        if (!suppress_action) {
            if (actions.at(PLAYER_PACMAN) == 0) {
                copy.successor.get_player(PLAYER_PACMAN).reverse();
            } else {
                REQUIRE(actions.at(PLAYER_PACMAN) == 1);
            }
        }

        copy.predecessor = copy.successor;
        copy.successor.init_successor(copy.predecessor);
        copy.suppress_action = !copy.successor.progress_timers(copy.predecessor, uihints);
        copy.state = REVERSE_ALL_CHOICE;
    }

    return copy;
}

unsigned char IntermediateGameState::get_action_count(int player_index) const {
    if (suppress_action) {
        return 0;
    }
    else if (state == REVERSE_ALL_CHOICE) {
        return 2;  // either you reverse, or you don't
    }
    else if (state == REVERSE_PACMAN_CHOICE) {
        if (player_index == PLAYER_PACMAN) {
            return 2;
        } else {
            return 0;
        }
    }
    else if (state == ABOUT_TO_ACT) {
        return successor.get_player(player_index).get_action_count();
    }
}

Action IntermediateGameState::get_action_along_direction(int player_index, Direction::Type direction) const {
    REQUIRE(get_action_count(player_index) > 0);
    if (state == ABOUT_TO_ACT) {
        return successor.get_player(player_index).get_action_along_direction(direction);
    }
    else {
        return 0;  // just assume 0, even though that's not always correct (only affects testing / manual run)
    }
}

}}
