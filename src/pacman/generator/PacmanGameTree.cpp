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
using std::cout;
using std::endl;

namespace PACMAN {
    namespace GENERATOR {

// note: you may call child() max_rounds times without calling parent()
PacmanGameTree::PacmanGameTree(int max_rounds)
:   max_depth(max_rounds)
{
    REQUIRE(max_depth >= 0);
    INVARIANTS_ON_EXIT;
    states.reserve(max_depth + 1);  // Note: this is probably too much as sometimes multiple players need to move at the same time in the same tick
    intermediate_states.reserve(max_depth+1);  // Note: this is probably too much as sometimes multiple players need to move at the same time in the same tick

    // progress to initial choice
    GameState state(GameState::new_game());
    states.push_back(state);  // the initial state is a bit of a weird special case...
    intermediate_states.push_back(state);
}

PacmanGameTree::PacmanGameTree(std::istream& in)
{
    INVARIANTS_ON_EXIT;
    read(in, max_depth);

    states.reserve(max_depth+1);
    {
        vector<GameState>::size_type size;
        read(in, size);
        for (int i=0; i < size; ++i) {
            states.emplace_back(GameState(in));
        }
        ASSERT(states.size() == size);
    }

    intermediate_states.reserve(max_depth+1);
    {
        vector<GameState>::size_type size;
        read(in, size);
        for (int i=0; i < size; ++i) {
            intermediate_states.emplace_back(GameState(in));
        }
        ASSERT(intermediate_states.size() == size);
    }
}

void PacmanGameTree::parent() {
    INVARIANTS_ON_EXIT;
    states.pop_back();
    intermediate_states.pop_back();
}

void PacmanGameTree::child(const vector<Action>& actions) {
    INVARIANTS_ON_EXIT;
    REQUIRE(actions.size() == PLAYER_COUNT);

    const int old_states_size = states.size();
    const int old_intermediate_states_size = intermediate_states.size();

    // proceed to next state
    GameState state = intermediate_states.back();
    state.act(actions, states.back(), uihints);

    // proceed even further
    progress_game_until_choice(state);

    ENSURE(states.size() == old_states_size + 1);
    ENSURE(intermediate_states.size() == old_intermediate_states_size + 1);
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
    return intermediate_states.back().get_player(player).get_legal_actions();
}

/*
 * Tries to generate actions from prev_actions
 *
 * actions: generated actions are stored here. Its original contents are ignored.
 *
 * Returns true if it succeeded, false if choices need to be made
 */
bool PacmanGameTree::generate_actions(const GameState& state, vector<Action>& actions) const {
    actions.clear();
    for (int player=0; player < PLAYER_COUNT; ++player) {
        auto legal_actions = state.get_player(player).get_legal_actions();
        if (legal_actions.count <= 1) {
            actions.push_back(0);
        }
        else if (legal_actions.count == 2 && legal_actions.reverse_action >= 0) {
            if (legal_actions.reverse_action == 1) {
                actions.push_back(0);
            }
            else {
                actions.push_back(1);
            }
        }
        else {
            return false;
        }
    }
    return true;
}

/*
 * Progress game state until game over or a player has a choice
 *
 * state: a final state
 */
void PacmanGameTree::progress_game_until_choice(GameState& state) {
    INVARIANTS_ON_EXIT;

    GameState intermediate_state = GameState(state, uihints);

    // progress as far as possible
    vector<Action> actions;
    actions.reserve(PLAYER_COUNT);
    while (!state.is_game_over() && generate_actions(intermediate_state, actions)) {
        intermediate_state.act(actions, state, uihints);
        state = intermediate_state;

        intermediate_state = GameState(state, uihints);
    }

    // push state
    states.push_back(state);
    intermediate_states.push_back(intermediate_state);
}

void PacmanGameTree::save(std::ostream& out) const {
    write(out, max_depth);

    write(out, states.size());
    for (auto state : states) {
        state.save(out);
    }

    write(out, intermediate_states.size());
    for (auto state : intermediate_states) {
        state.save(out);
    }
}

bool PacmanGameTree::operator==(const PacmanGameTree& other) const {
    return other.max_depth == max_depth &&
        other.states == states &&
        other.intermediate_states == intermediate_states;
}

void PacmanGameTree::invariants() const {
    INVARIANT(states.capacity() == max_depth + 1);
    INVARIANT(intermediate_states.capacity() == max_depth + 1);
    INVARIANT(!states.empty());
    INVARIANT(!intermediate_states.empty());
}

int PacmanGameTree::get_max_depth() const {
    ENSURE(max_depth >= 0);
    return max_depth;
}

}}
