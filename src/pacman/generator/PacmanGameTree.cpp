/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "PacmanGameTree.h"

#include "ChoiceNode.h"
#include "../model/GameState.h"
#include "../model/PacmanNodes.h"
#include "../model/GhostNodes.h"
#include "../Constants.h"

#include <boost/scope_exit.hpp>

using namespace PACMAN::MODEL;
using namespace PACMAN::SPECIFICATION;
using std::vector;

namespace PACMAN {
    namespace GENERATOR {

PacmanGameTree::PacmanGameTree(int max_depth) 
:   max_depth(max_depth)
{
    INVARIANTS_ON_EXIT;
    states.reserve(max_depth+1);  // Note: this is probably too much as sometimes multiple players need to move at the same time in the same tick

    // progress to initial choice
    GameState state(PACMAN_NODES.get_spawn(), GHOST_NODES.get_spawns());
    Action prev_actions[PLAYER_COUNT] = {-1, -1, -1, -1, -1};  // no previous actions
    progress_game_until_choice(state, prev_actions);
}

void PacmanGameTree::parent() {
    INVARIANTS_ON_EXIT;
    states.pop_back();
    ENSURE(!states.empty());
}

void PacmanGameTree::child(const vector<Action>& actions) {
    INVARIANTS_ON_EXIT;
    REQUIRE(actions.size() == PLAYER_COUNT);

    const int old_states_size = states.size();

    // proceed to next state
    GameState state = states.back();
    state = GameState(actions.data(), &state, uihints);

    // proceed even further
    auto copied_actions = actions;
    progress_game_until_choice(state, copied_actions.data());

    ENSURE(states.size() == old_states_size + 1);
}

bool PacmanGameTree::is_leaf() const {
    return states.back().is_game_over();
}

int PacmanGameTree::get_score() const {
    return states.back().get_score();
}

LegalActions PacmanGameTree::get_legal_actions(int player) const {
    REQUIRE(player >= 0);
    REQUIRE(player < PLAYER_COUNT);
    return states.back().get_player(player).get_legal_actions();
}

/*
 * Tries to generate actions from prev_actions
 *
 * actions: generated actions are stored here. Its original contents are ignored.
 *
 * Returns true if it succeeded, false if choices need to be made
 */
bool PacmanGameTree::generate_actions(const GameState& state, Action* prev_actions, Action* actions) {
    REQUIRE(prev_actions != NULL);
    REQUIRE(actions != NULL);

    for (int player=0; player < PLAYER_COUNT; ++player) {
        auto legal_actions = state.get_player(player).get_legal_actions();
        if (legal_actions.count == 0) {
            REQUIRE(prev_actions[player] >= 0);
            actions[player] = prev_actions[player];
        } else if (legal_actions.count == 1) {
            actions[player] = 0;
        } else {
            return false;
        }
    }
    return true;
}

/*
 * Progress game state until game over or a player has a choice
 */
void PacmanGameTree::progress_game_until_choice(GameState& state, Action* prev_actions) {
    INVARIANTS_ON_EXIT;
    REQUIRE(prev_actions != NULL);

    // progress as far as possible
    Action other_actions[PLAYER_COUNT];
    Action* actions = other_actions;
    while (!state.is_game_over() && generate_actions(state, prev_actions, actions)) {
        state = GameState(actions, &state, uihints);
        std::swap(prev_actions, actions);
    }

    // push state
    states.push_back(state);
}


void PacmanGameTree::invariants() const {
    INVARIANT(states.capacity() == max_depth + 1);
}

}}
