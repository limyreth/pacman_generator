/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "IntermediateGameState.h"
#include "../util/assertion.h"
#include "../model/PacmanNodes.h"
#include "../model/GhostNodes.h"
#include "../Constants.h"

using std::vector;
using std::cout;
using std::endl;
using namespace ::PACMAN::SPECIFICATION;

namespace PACMAN {
    namespace MODEL {

// intermediate state with new_game as predecessor
IntermediateGameState::IntermediateGameState(const GameState predecessor)
:   predecessor(predecessor),
    successor(predecessor),
    suppress_action(false),
    state(ABOUT_TO_ACT)
{
    for (unsigned int i = 0u; i < PLAYER_COUNT; ++i) {
        movement_excess[i] = 0.0;
    }
}

IntermediateGameState IntermediateGameState::new_game() {
    return IntermediateGameState(GameState(PACMAN_NODES.get_spawn(), GHOST_NODES.get_spawns()));
}

bool IntermediateGameState::operator==(const IntermediateGameState& o) const {
    for (unsigned int i = 0u; i < PLAYER_COUNT; ++i) {
        if (o.movement_excess[i] != movement_excess[i]) {
            return false;
        }
    }

    return o.predecessor == predecessor &&
        o.successor == successor &&
        o.suppress_action == suppress_action &&
        o.state == state;
}

IntermediateGameState IntermediateGameState::act(const std::vector<Action>& actions, GameStateObserver& observer) const {
    REQUIRE(state != GAME_OVER);  // iff get_predecessor().is_game_over()
    auto copy = *this;

    if (state == REVERSE_ALL_CHOICE) {
        if (!suppress_action) {
            for (unsigned int player_index = 0u; player_index < PLAYER_COUNT; ++player_index) {
                if (actions.at(player_index) == 1u) {
                    copy.successor.get_player(player_index).reverse();
                } else {
                    REQUIRE(actions.at(player_index) == 0u);
                }
            }
        }

        copy.successor.initial_movement(copy.predecessor, observer, copy.movement_excess);
        copy.suppress_action = false;
        copy.state = ABOUT_TO_ACT;
    }
    else if (state == ABOUT_TO_ACT) {
        ASSERT(!suppress_action);
        copy.suppress_action = !copy.successor.act(actions, predecessor, observer, movement_excess);
        copy.state = REVERSE_PACMAN_CHOICE;
    }
    else if (state == REVERSE_PACMAN_CHOICE) {
        copy.predecessor = copy.successor;

        if (successor.is_game_over()) {
            copy.successor = GameState();  // there is no successor
            copy.state = GAME_OVER;
        }
        else {
            if (!suppress_action) {
                if (actions.at(PLAYER_PACMAN) == 1u) {
                    copy.successor.get_player(PLAYER_PACMAN).reverse();
                } else {
                    REQUIRE(actions.at(PLAYER_PACMAN) == 0u);
                }
            }

            copy.successor.init_successor(copy.predecessor);
            copy.suppress_action = !copy.successor.progress_timers(copy.predecessor, observer);
            copy.state = REVERSE_ALL_CHOICE;
        }
    }

    return copy;
}

unsigned int IntermediateGameState::get_action_count(unsigned int player_index) const {
    REQUIRE(state != GAME_OVER);
    if (suppress_action) {
        return 0u;
    }
    else if (state == REVERSE_ALL_CHOICE) {
        if (successor.get_player(player_index).can_reverse()) {
            return 2u;
        }
        else {
            return 1u;
        }
    }
    else if (state == REVERSE_PACMAN_CHOICE) {
        if (player_index == PLAYER_PACMAN) {
            return 2u;
        } else {
            return 0u;
        }
    }
    else {
        ASSERT(state == ABOUT_TO_ACT);
        return successor.get_player(player_index).get_action_count();
    }
}

Action IntermediateGameState::get_action_along_direction(unsigned int player_index, Direction::Type direction) const {
    REQUIRE(state != GAME_OVER);
    REQUIRE(get_action_count(player_index) > 0u);
    if (state == ABOUT_TO_ACT) {
        return successor.get_player(player_index).get_action_along_direction(direction);
    }
    else {
        return 0u;  // just assume 0, even though that's not always correct (only affects testing / manual run)
    }
}

}}
