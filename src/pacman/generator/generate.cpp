/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "generate.h"

#include "../model/GameState.h"
#include "../model/PacmanNodes.h"
#include "../model/GhostNodes.h"
#include "../Constants.h"
#include "../util/assertion.h"

namespace PACMAN {

    using namespace MODEL;
    using namespace SPECIFICATION;

    namespace GENERATOR {

static const int MAX_CHOICES = 100;  // the max depth of choices to generate into

Generator::Generator() 
:   choices(MAX_CHOICES),
    states(MAX_CHOICES),  // Note: this is probably too much as sometimes multiple players need to move at the same time in the same tick
    choice_index(MAX_CHOICES),
    state_index(MAX_CHOICES),
    search_complete(false),
    initialised(false)
{
    get_state() = GameState(PACMAN_NODES.get_spawn(), GHOST_NODES.get_spawns());

    // progress to initial choice
    int next_player = progress_game_until_choice(get_state());
    ASSERT(next_player > -1); // the game of pacman has choices
    push_child(next_player);

    initialised = true;
    ASSERT_INVARIANTS();
}

void Generator::run() {
    minimax();
}

int Generator::get_alpha() const {
    int i = choice_index;
    while (i < choices.size()) {
        if (get(i).player == 0) {
            return get(i).alpha_beta;
        }
        ++i;
    }
    return 0;
}

int Generator::get_beta() const {
    int i = choice_index;
    while (i < choices.size()) {
        if (get(i).player != 0) {
            return get(i).alpha_beta;
        }
        ++i;
    }
    return 999999999; // +infinity TODO calculate and set this to MAX_SCORE, have it in Spec constants
}

/*
 * Returns true if player has multiple legal actions to act upon the current state
 */
bool Generator::has_choice(int player) const {
    REQUIRE(player >= 0);
    REQUIRE(player < PLAYER_COUNT);
    LegalActions legal_actions;
    get_state().get_player(player).get_legal_actions(legal_actions);
    return legal_actions.count > 1;
}

/*
 * Returns first player that still needs to choose an action for next tick
 *
 * Returns -1 if no player has a choice.
 *
 * player: index of first player that might have a choice
 */
int Generator::get_first_undecided(int player) const {
    REQUIRE(player >= 0);
    REQUIRE(player < PLAYER_COUNT);

    while (!has_choice(player)) {
        ++player;
        if (player == PLAYER_COUNT) {
            player = -1;
            break;
        }
    }

    ENSURE(player < PLAYER_COUNT);
    return player;
}

/*
 * Progresses the game up til game over, or the next choice
 *
 * Makes use of this->choices when necessary.
 *
 * Returns the player who has to make a choice, or -1 if game over
 */
int Generator::progress_game_state() {
    REQUIRE(get().action > -1);  // current player has chosen

    // sufficient choices made to proceed to next state?
    int next_player = get().player + 1;
    if (next_player < PLAYER_COUNT) {
        next_player = get_first_undecided(next_player);
    }
    else {
        next_player = -1;
    }

    if (next_player == -1) {
        GameState state = get_state();

        // get actions
        Action actions[PLAYER_COUNT] = {-1, -1, -1, -1, -1};
        for (int i=0; i<=get().player; ++i) {
            if (has_choice(i)) {
                // TODO extract get_action(i)
                int j = choice_index;
                while (j < choices.size()) {
                    if (get(j).player == i) {
                        actions[i] = get(j).action;
                        break;
                    }
                    ++j;
                }
                ENSURE(actions[i] > -1);
            }
            else {
                actions[i] = 0;
            }
        }

        // proceed to next state
        state = GameState(actions, &state, uihints);

        progress_game_until_choice(state);
    }
    
    ENSURE(get_state().is_game_over() || has_choice(next_player));
    ENSURE(!get_state().is_game_over() || next_player == -1);
    ASSERT_INVARIANTS();
    return next_player;
}

/*
 * Progress game state until game over or a player has a choice
 */
int Generator::progress_game_until_choice(GameState& state) {
    int next_player = -1;

    // progress as far as possible
    Action actions[PLAYER_COUNT] = {0, 0, 0, 0, 0};
    while (!state.is_game_over() && (next_player = get_first_undecided(0)) == -1) {
        state = GameState(actions, &state, uihints);
    }

    // push state
    --state_index;
    states.at(state_index) = state;

    ENSURE(get_state().is_game_over() || has_choice(next_player));
    ENSURE(!get_state().is_game_over() || next_player == -1);
    ASSERT_INVARIANTS();
    return next_player;
}

/*
 * Push child node onto stack (of the search tree)
 */
void Generator::push_child(int next_player) {
    REQUIRE(next_player >= 0);
    REQUIRE(next_player < PLAYER_COUNT);

    REQUIRE(choice_index-1 >= 0);

    int alpha_beta = next_player == 0 ? get_alpha() : get_beta();
    --choice_index;
    get().player = next_player;
    get().action = -1;
    get().alpha_beta = alpha_beta;

    ASSERT_INVARIANTS();
}

/*
 * Pops current node
 */
void Generator::pop() {
    ++choice_index;

    if (choice_index == choices.size()) {
        // popped the last choice, search complete
        ++state_index;
        ASSERT(state_index == states.size());
        search_complete = true;
    }
    else if (get().player >= get(choice_index-1).player) {
        ++state_index;
    }

    ASSERT_INVARIANTS();
}

/*
 * Explore all choices of current choice node
 */
int Generator::minimax() {
    REQUIRE(!search_complete);

    LegalActions legal_actions;
    get_state().get_player(get().player).get_legal_actions(legal_actions);
    while (get().action+1 < legal_actions.count &&
            get_alpha() >= get_beta()) {  // alpha beta pruning
            
        // choose action
        ++get().action;

        const int next_player = progress_game_state();
        const int next_depth = choice_index - 1;

        // reached leaf node?
        if (next_player == -1 || next_depth < 0) {
            // TODO if is better than current best, save current path as best
            pop();
            return get_state().get_score();
        }

        // next choice point: move the stack pointer to make room for the child node
        push_child(next_player);

        // explore choices of this child
        int value = minimax();

        // process the alpha_beta value it returned
        if (get().player == 0) {
            if (value > get_alpha()) {
                get().alpha_beta = value;
            }
        }
        else {
            if (value < get_beta()) {
                get().alpha_beta = value;
            }
        }
        ASSERT_INVARIANTS();
    }

    // completed/discontinued search of subtree with this node as its root
    pop();

    ASSERT_INVARIANTS();
    return get().alpha_beta;
}

void Generator::invariants() {
    INVARIANT(states.capacity() == MAX_CHOICES);
    INVARIANT(state_index >= 0);
    INVARIANT(search_complete || state_index < states.size());  // state_index valid unless search_complete

    INVARIANT(choices.capacity() == MAX_CHOICES);
    INVARIANT(choice_index >= 0);
    INVARIANT(!initialised || search_complete || choice_index < MAX_CHOICES); // choice_index valid unless not initialised or search completed

    INVARIANT(state_index >= choice_index);

    INVARIANT(get_alpha() >= 0);
    INVARIANT(get_beta() >= 0);
    INVARIANT(get().player >= 0);

    // Invariant: the action field of all ancestors is valid and shows the path
    // to the current node
}


}}
