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
:   initialised(false)
{
    INVARIANTS_ON_EXIT;
    states.reserve(max_depth+1);  // Note: this is probably too much as sometimes multiple players need to move at the same time in the same tick

    states.emplace_back(PACMAN_NODES.get_spawn(), GHOST_NODES.get_spawns());
}

int PacmanGameTree::init() {
    INVARIANTS_ON_EXIT;

    // progress to initial choice
    int next_player = progress_game_until_choice(get_state());
    ASSERT(next_player > -1); // the game of pacman has choices

    initialised = true;
    return next_player;
}

void PacmanGameTree::parent(const vector<ChoiceNode>& choices) {
    INVARIANTS_ON_EXIT;
    REQUIRE(choices.size() > 1);
    REQUIRE(initialised);

    auto previous = choices.back();

    if (choices.back().player >= (*(choices.end()-2)).player) {
        states.pop_back();
    }

}

int PacmanGameTree::child(const vector<ChoiceNode>& choices) {
    INVARIANTS_ON_EXIT;
    REQUIRE(initialised);
    REQUIRE(choices.back().action < get_child_count(choices));

    const int next_player = progress_game_state(choices);
    return next_player;
}

int PacmanGameTree::get_score() const {
    REQUIRE(initialised);
    return get_state().get_score();
}

int PacmanGameTree::get_child_count(const vector<ChoiceNode>& choices) const {
    REQUIRE(initialised);
    LegalActions legal_actions;
    get_state().get_player(choices.back().player).get_legal_actions(legal_actions);
    return legal_actions.count;
}

/*
 * Returns true if player has multiple legal actions to act upon the current state
 */
bool PacmanGameTree::has_choice(const GameState& state, int player) const {
    REQUIRE(player >= 0);
    REQUIRE(player < PLAYER_COUNT);
    LegalActions legal_actions;
    state.get_player(player).get_legal_actions(legal_actions);
    return legal_actions.count > 1;
}
/*
 * Returns first player that still needs to choose an action for next tick
 *
 * Returns -1 if no player has a choice.
 *
 * player: index of last player that has chosen
 */
int PacmanGameTree::get_first_undecided(const GameState& state, int player) const {
    REQUIRE(player >= -1);
    REQUIRE(player < PLAYER_COUNT);

    int undecided_player = player;

    BOOST_SCOPE_EXIT(&player, &undecided_player) {
        ENSURE(undecided_player < PLAYER_COUNT);
        ENSURE(undecided_player == -1 || undecided_player > player);
    } BOOST_SCOPE_EXIT_END

    do {
        ++undecided_player;
        if (undecided_player == PLAYER_COUNT) {
            return undecided_player = -1;
        }
    } while (!has_choice(state, undecided_player));

    return undecided_player;
}

/*
 * Get action of desired_player for current round
 *
 * Returns -1 if no choice was made for the player
 */
int PacmanGameTree::get_action(int desired_player, const std::vector<ChoiceNode>& choices) const {
    REQUIRE(desired_player >= 0);
    REQUIRE(desired_player < PLAYER_COUNT);

    if (has_choice(get_state(), desired_player)) {
        int prev_player = PLAYER_COUNT;
        for (auto it = choices.rbegin(); it != choices.rend(); it++) {
            auto player = (*it).player;
            if (player >= prev_player) {
                return -1;  // no choice made for this player
            }
            if (player == desired_player) {
                return (*it).action;
            }
            prev_player = player;
        }
    }
    else {
        return 0;
    }
    ASSERT(false);
}

/*
 * Progresses the game up til game over, or the next choice
 *
 * Returns the player who has to make a choice, or -1 if game over
 */
int PacmanGameTree::progress_game_state(const vector<ChoiceNode>& choices) {
    INVARIANTS_ON_EXIT;
    REQUIRE(choices.back().action > -1);  // current player has chosen

    // sufficient choices made to proceed to next state?
    int next_player = get_first_undecided(get_state(), choices.back().player);

    if (next_player == -1) {
        int old_states_size = states.size();
        GameState state = get_state();

        // get actions
        Action actions[PLAYER_COUNT] = {-1, -1, -1, -1, -1};
        for (int i=0; i<PLAYER_COUNT; ++i) {
            actions[i] = get_action(i, choices);
            ASSERT(actions[i] >= 0);  // each player should have chosen by now
        }

        // proceed to next state
        state = GameState(actions, &state, uihints);

        // proceed even further
        next_player = progress_game_until_choice(state);

        ASSERT(states.size() == old_states_size + 1);
    }

    ENSURE(get_state().is_game_over() || has_choice(get_state(), next_player));
    ENSURE(!get_state().is_game_over() || next_player == -1);
    return next_player;
}

/*
 * Progress game state until game over or a player has a choice
 */
int PacmanGameTree::progress_game_until_choice(GameState& state) {
    INVARIANTS_ON_EXIT;
    int next_player = -1;

    // progress as far as possible
    Action actions[PLAYER_COUNT] = {0, 0, 0, 0, 0};
    while (!state.is_game_over() && (next_player = get_first_undecided(state, -1)) == -1) {
        state = GameState(actions, &state, uihints);
    }

    // push state
    states.push_back(state);

    ENSURE(get_state().is_game_over() || has_choice(get_state(), next_player));
    ENSURE(!get_state().is_game_over() || next_player == -1);
    return next_player;
}


void PacmanGameTree::invariants() const {
    REQUIRE(!states.empty());
}

}}
