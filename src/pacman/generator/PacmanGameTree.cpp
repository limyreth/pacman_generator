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
#include "../Constants.h"
#include "../util/serialization.h"

#include <boost/scope_exit.hpp>

using namespace PACMAN::MODEL;
using namespace PACMAN::SPECIFICATION;
using std::vector;
using std::endl;

namespace PACMAN {
    namespace GENERATOR {

// note: you may call child() max_rounds times without calling parent()
PacmanGameTree::PacmanGameTree(int max_rounds)
:   max_depth(max_rounds)
{
    INVARIANTS_ON_EXIT;
    states.reserve(max_depth+1);  // Note: this is probably too much as sometimes multiple players need to move at the same time in the same tick

    // progress to initial choice
    GameState state(GameState::new_game());
    vector<Action> prev_actions(PLAYER_COUNT, -1);
    progress_game_until_choice(state, prev_actions);
}

PacmanGameTree::PacmanGameTree(std::istream& in)
:   max_depth(-1)
{
    INVARIANTS_ON_EXIT;
    read(in, max_depth);
    states.reserve(max_depth+1);

    vector<GameState>::size_type size;
    read(in, size);
    for (int i=0; i < size; ++i) {
        states.emplace_back(GameState(in));
    }
    ASSERT(states.size() == size);
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
    state = GameState(actions, state, uihints);

    // proceed even further
    progress_game_until_choice(state, actions);

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
bool PacmanGameTree::generate_actions(const GameState& state, vector<Action>& prev_actions, vector<Action>& actions) const {
    //REQUIRE(prev_actions.size() == PLAYER_COUNT);

    actions.clear();
    for (int player=0; player < PLAYER_COUNT; ++player) {
        auto legal_actions = state.get_player(player).get_legal_actions();
        if (legal_actions.count == 0) {
            REQUIRE(prev_actions.at(player) >= 0);
            actions.push_back(prev_actions.at(player));
        } else if (legal_actions.count == 1) {
            actions.push_back(0);
        } else {
            return false;
        }
    }
    return true;
}

/*
 * Progress game state until game over or a player has a choice
 */
void PacmanGameTree::progress_game_until_choice(GameState& state, vector<Action> prev_actions) {
    INVARIANTS_ON_EXIT;
    REQUIRE(prev_actions.size() == PLAYER_COUNT);

    // progress as far as possible
    vector<Action> actions;
    actions.reserve(PLAYER_COUNT);
    while (!state.is_game_over() && generate_actions(state, prev_actions, actions)) {
        state = GameState(actions, state, uihints);
        prev_actions.swap(actions);
    }

    // push state
    states.push_back(state);
}

void PacmanGameTree::save(std::ostream& out) const {
    write(out, max_depth);

    write(out, states.size());
    for (auto state : states) {
        state.save(out);
    }
}

void PacmanGameTree::invariants() const {
    INVARIANT(states.capacity() == max_depth + 1);
}

}}
