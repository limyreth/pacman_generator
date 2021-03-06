/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "ChoiceTree.h"

#include "ChoiceNode.h"
#include "GameTree.h"
#include "../util/serialization.h"

using namespace ::PACMAN::MODEL;
using std::vector;
using std::cout;
using std::endl;
using std::max;

namespace PACMAN {
    namespace GENERATOR {

ChoiceTree::ChoiceTree(GameTree& tree, unsigned int max_choices)
:   max_choices(max_choices),
    choices_taken(0),
    tree(tree)
{
    INVARIANTS_ON_EXIT;
    init();
    choices.emplace_back(ChoiceNode{-1u, -1});
}

ChoiceTree::ChoiceTree(std::istream& in, GameTree& tree)
:   tree(tree)
{
    INVARIANTS_ON_EXIT;
    read(in, max_choices);
    read(in, choices_taken);

    init();

    vector<ChoiceNode>::size_type size;
    read(in, size);
    choices.resize(size);

    in.read((char*)choices.data(), choices.size() * sizeof(ChoiceNode));

    restore_game_tree();
}

void ChoiceTree::restore_game_tree() const {
    REQUIRE(tree.is_root());

    // get back to where we were in the game tree
    int finished_rounds = (choices.size() - 1) / PLAYER_COUNT;
    auto it = choices.begin();
    for (int i=0; i < finished_rounds; ++i) {
        enter_child(it);
    }
}

void ChoiceTree::init() {
    cout << "Searching with a max of " << max_choices << " choices" << endl;
    tree.init(max_choices);
    choices.reserve(get_max_depth()+1);
}

Action ChoiceTree::parent() {
    INVARIANTS_ON_EXIT;
    choices.pop_back();
    if (choices.size() % PLAYER_COUNT == 0) {
        tree.parent();
    }
    if (tree.get_action_count(get_player(get_depth())) > 1u) {
        choices_taken--;
    }
    ENSURE(!is_leaf());
    return choices.back().action;
}

bool ChoiceTree::next_child() {
    INVARIANTS_ON_EXIT;
    REQUIRE(!is_leaf());

    auto action_count = tree.get_action_count(get_player(get_depth()));

    if (action_count == 0u) {
        if (!is_first_child()) {
            return false;
        }
        choices.back().action = -2u;  // we encode first child as -1
    }
    else {
        Action next_action = choices.back().action + 1u;
        if (next_action < action_count) {
            choices.back().action = next_action;
        }
        else {
            return false;
        }
    }

    if (action_count > 1) {
        choices_taken++;
    }

    if (get_player(get_depth()) == PLAYER_COUNT - 1u) {
        auto it = (vector<ChoiceNode>::const_iterator)choices.end() - PLAYER_COUNT;
        enter_child(it);
        ASSERT(it == choices.end());
    }

    choices.emplace_back(ChoiceNode{-1u, -1});

    return true;
}

unsigned int ChoiceTree::get_player(unsigned int depth) const {
    return depth % PLAYER_COUNT;
}

/*
 * Call GameTree.child with choices starting with it
 */
void ChoiceTree::enter_child(vector<ChoiceNode>::const_iterator& it) const {
    //REQUIRE(it <= choices.end() - PLAYER_COUNT)
    vector<Action> actions;
    actions.reserve(PLAYER_COUNT);
    for (unsigned int player_index = 0u; player_index < PLAYER_COUNT; ++player_index) {
        ASSERT(it != choices.end());
        actions.push_back((*it).action);
        it++;
    }
    tree.child(actions);
}

bool ChoiceTree::is_leaf() const {
    return tree.is_leaf() || choices_taken == max_choices;
}

bool ChoiceTree::is_first_child() const {
    REQUIRE(!is_leaf());
    return choices.back().action == -1u;
}

int ChoiceTree::get_score() const {
    return tree.get_score();
}

unsigned int ChoiceTree::get_depth() const {
    return choices.size()-1u;
}

unsigned int ChoiceTree::get_max_depth() const {
    int retval = max_choices * PLAYER_COUNT;
    ENSURE(retval >= 0);
    return retval;
}

const GENERATOR::ChoiceNode& ChoiceTree::get() const {
    return choices.back();
}

const GENERATOR::ChoiceNode& ChoiceTree::get(int depth) const {
    return choices.at(depth);
}

void ChoiceTree::set_alpha_beta(int alpha_beta) {
    INVARIANTS_ON_EXIT;
    choices.back().alpha_beta = alpha_beta;
}

void ChoiceTree::save(std::ostream& out) const {
    write(out, max_choices);
    write(out, choices_taken);
    write(out, choices.size());
    out.write((const char*)choices.data(), choices.size() * sizeof(ChoiceNode));
}

bool ChoiceTree::operator==(const ChoiceTree& o) const {
    return o.choices == choices &&
        o.max_choices == max_choices &&
        o.choices_taken == choices_taken &&
        o.tree == tree;
}

void ChoiceTree::invariants() const {
    INVARIANT(!choices.empty());
    INVARIANT(choices_taken <= max_choices);
    INVARIANT(choices.size() > choices_taken);
    INVARIANT(choices.capacity() == get_max_depth() + 1);
    //INVARIANT(max_choices const after ctor)
}

double ChoiceTree::get_completion() const {
    double completion = 0.0;
    
    for (unsigned int depth = get_depth(); depth <= get_depth(); --depth) {
        if (depth != get_depth()) {
            if (get_player(depth) == PLAYER_COUNT-1u) {
                tree.parent();
            }
        }

        unsigned int action_count = 1;
        int children_done;
        auto action = get(depth).action;
        if (action == -1u) {
            children_done = 0;
        }
        else if (action == -2u) {
            if (depth == get_depth()) {
                children_done = 1;
            }
            else {
                children_done = 0;
            }
        }
        else {
            action_count = tree.get_action_count(get_player(depth));
            ASSERT(action >= 0u);
            ASSERT(action_count > 0u);
            if (depth == get_depth()) {
                children_done = action + 1u;
            }
            else {
                children_done = action;
            }
        }

        completion = children_done / (double)action_count + // children fully done
                     1.0 / (double)action_count * completion;  // + partial completion of current child

        ASSERT(completion >= 0.0);
        ASSERT(completion <= 1.0);
    }

    // restore the game tree
    restore_game_tree();

    //ENSURE(game_tree hasn't changed)
    ENSURE(completion >= 0.0);
    ENSURE(completion <= 1.0);
    return completion;
}

}}
