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
#include "../Constants.h"
#include "../util/serialization.h"

#include <boost/scope_exit.hpp>

using namespace PACMAN::MODEL;
using namespace PACMAN::SPECIFICATION;
using std::vector;
using std::cout;
using std::endl;

namespace PACMAN {
    namespace GENERATOR {

PacmanGameTree::PacmanGameTree()
:   initialised(false)
{
}

// note: you may call child() max_rounds times without calling parent()
void PacmanGameTree::init(unsigned int max_rounds) {
    REQUIRE(!initialised);
    initialised = true;

    max_depth = max_rounds;
    states.reserve(max_depth+1);  // Note: this is probably too much as sometimes multiple players need to move at the same time in the same tick

    // progress to initial choice
    states.emplace_back(IntermediateGameState::new_game());
}

void PacmanGameTree::parent() {
    INVARIANTS_ON_EXIT;
    REQUIRE(initialised);
    states.pop_back();
}

void PacmanGameTree::child(const vector<Action>& actions) {
    INVARIANTS_ON_EXIT;
    REQUIRE(initialised);
    REQUIRE(actions.size() == PLAYER_COUNT);

    const int old_states_size = states.size();

    // proceed to next state
    auto intermediate = states.back().act(actions, uihints);

    // proceed even further
    progress_game_until_choice(intermediate);

    ENSURE(states.size() == old_states_size + 1);
}

bool PacmanGameTree::is_leaf() const {
    REQUIRE(initialised);
    return states.back().get_predecessor().is_game_over();
}

int PacmanGameTree::get_score() const {
    REQUIRE(initialised);
    return states.back().get_predecessor().get_score();
}

unsigned char PacmanGameTree::get_action_count(int player) const {
    REQUIRE(player >= 0);
    REQUIRE(player < PLAYER_COUNT);
    return states.back().get_player(player).get_action_count();
}

/*
 * Tries to generate actions from prev_actions
 *
 * actions: generated actions are stored here. Its original contents are ignored.
 *
 * Returns true if it succeeded, false if choices need to be made
 */
bool PacmanGameTree::generate_actions(const IntermediateGameState& state, vector<Action>& actions) const {
    actions.clear();
    for (int player=0; player < PLAYER_COUNT; ++player) {
        auto action_count = state.get_player(player).get_action_count();
        if (action_count <= 1) {
            actions.push_back(0);
        }
        else {
            return false;
        }
    }
    return true;
}

/*
 * Progress game state until game over or a player has a choice
 */
void PacmanGameTree::progress_game_until_choice(IntermediateGameState& state) {
    INVARIANTS_ON_EXIT;

    // progress as far as possible
    vector<Action> actions;
    actions.reserve(PLAYER_COUNT);
    while (!state.get_predecessor().is_game_over() && generate_actions(state, actions)) {
        state = state.act(actions, uihints);
    }

    // push state
    states.push_back(state);
}

bool PacmanGameTree::operator==(const PacmanGameTree& o) const {
    if (o.states.size() != states.size()) {
        return false;
    }

    for (int i=0; i < states.size(); ++i) {
        if (o.states.at(i) != states.at(i)) {
            return false;
        }
    }

    return o.max_depth == max_depth;
}

void PacmanGameTree::invariants() const {
    INVARIANT(states.capacity() == max_depth + 1);
    INVARIANT(!states.empty());
}

int PacmanGameTree::get_max_depth() const {
    ENSURE(max_depth >= 0);
    return max_depth;
}

}}
