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
    const auto old_states_size = states.size();

    auto intermediate = states.back().act(actions, state_observer);
    progress_game_until_choice(intermediate);

    ENSURE(states.size() == old_states_size + 1u);
}

bool PacmanGameTree::is_leaf() const {
    REQUIRE(initialised);
    return states.back().get_predecessor().is_game_over();
}

int PacmanGameTree::get_score() const {
    REQUIRE(initialised);
    return states.back().get_predecessor().get_score();
}

unsigned int PacmanGameTree::get_action_count(unsigned int player_index) const {
    REQUIRE(initialised);
    REQUIRE(player_index < PLAYER_COUNT);
    return states.back().get_action_count(player_index);
}

/*
 * Tries to generate actions from prev_actions
 *
 * actions: generated actions are stored here. Its original contents are ignored.
 *
 * Returns true if it succeeded, false if choices need to be made
 */
bool PacmanGameTree::generate_actions(const IntermediateGameState& state, vector<Action>& actions) const {
    //REQUIRE(initialised);
    actions.clear();
    for (unsigned int player_index = 0u; player_index < PLAYER_COUNT; ++player_index) {
        auto action_count = state.get_action_count(player_index);
        if (action_count <= 1u) {
            actions.push_back(0u);
        }
        else {
            return false;
        }
    }
    ENSURE(actions.size() == PLAYER_COUNT);
    return true;
}

/*
 * Progress game state until game over or a player has a choice
 */
void PacmanGameTree::progress_game_until_choice(IntermediateGameState& state) {
    INVARIANTS_ON_EXIT;
    //REQUIRE(initialised);

    // progress as far as possible
    vector<Action> actions;
    actions.reserve(PLAYER_COUNT);
    while (!state.get_predecessor().is_game_over() && generate_actions(state, actions)) {
        state = state.act(actions, state_observer);
    }

    // push state
    states.push_back(state);
}

bool PacmanGameTree::operator==(const GameTree& generic_o) const {
    auto pointer = dynamic_cast<const PacmanGameTree*>(&generic_o);
    if (pointer == NULL) {
        return false;
    }

    auto o = *pointer;

    if (o.states.size() != states.size()) {
        return false;
    }

    for (unsigned int i=0u; i < states.size(); ++i) {
        if (o.states.at(i) != states.at(i)) {
            return false;
        }
    }

    return o.max_depth == max_depth;
}

void PacmanGameTree::invariants() const {
    INVARIANT(states.capacity() == max_depth + 1);
    INVARIANT(!states.empty());
    //INVARIANT(max_depth is const after init)
}

bool PacmanGameTree::is_root() const {
    return states.size() == 1;
}

}}
