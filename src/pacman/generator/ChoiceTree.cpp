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
using std::endl;
using std::max;

namespace PACMAN {
    namespace GENERATOR {

ChoiceTree::ChoiceTree(GameTree& tree, unsigned int max_choices)
:   tree(tree),
    max_choices(max_choices),
    choices_taken(0)
{
    INVARIANTS_ON_EXIT;
    init();
    choices.emplace_back(ChoiceNode{-1, 0, -1});
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
    tree.init(max_choices);
    choices.reserve(get_max_depth()+1);
}

int ChoiceTree::parent() {
    INVARIANTS_ON_EXIT;
    choices.pop_back();
    if (choices.size() % PLAYER_COUNT == 0) {
        tree.parent();
    }
    if (tree.get_action_count(choices.back().player) > 1) {
        choices_taken--;
    }
    ENSURE(!is_leaf());
    return choices.back().action;
}

bool ChoiceTree::next_child() {
    INVARIANTS_ON_EXIT;
    REQUIRE(!is_leaf());

    auto action_count = tree.get_action_count(choices.back().player);

    if (action_count == 0) {
        if (!is_first_child()) {
            return false;
        }
        choices.back().action = -2;  // we encode first child as -1
    }
    else {
        Action next_action = choices.back().action + 1;
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

    if (choices.size() % PLAYER_COUNT == 0) {
        auto it = (vector<ChoiceNode>::const_iterator)choices.end() - PLAYER_COUNT;
        enter_child(it);
    }

    choices.emplace_back(ChoiceNode{-1, (int)choices.size() % PLAYER_COUNT, -1});

    return true;
}

/*
 * Call GameTree.child with choices starting with it
 */
void ChoiceTree::enter_child(vector<ChoiceNode>::const_iterator& it) const {
    //REQUIRE(it <= choices.end() - PLAYER_COUNT)
    vector<Action> actions;
    actions.reserve(PLAYER_COUNT);
    for (int i=0; i < PLAYER_COUNT; ++i) {
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
    return choices.back().action == -1;
}

int ChoiceTree::get_score() const {
    return tree.get_score();
}

int ChoiceTree::get_depth() const {
    return choices.size()-1;
}

int ChoiceTree::get_max_depth() const {
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
    
    for (auto it = choices.rbegin(); it != choices.rend(); it++) {
        if (it != choices.rbegin()) {
            if (it->player == PLAYER_COUNT-1) {
                tree.parent();
            }
        }

        int action_count = 1;
        int children_done;
        if (it->action == -1) {
            children_done = 0;
        }
        else if (it->action == -2) {
            if (it == choices.rbegin()) {
                children_done = 1;
            }
            else {
                children_done = 0;
            }
        }
        else {
            action_count = tree.get_action_count(it->player);
            ASSERT(it->action >= 0);
            ASSERT(action_count > 0);
            if (it == choices.rbegin()) {
                children_done = it->action + 1;
            }
            else {
                children_done = it->action;
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
