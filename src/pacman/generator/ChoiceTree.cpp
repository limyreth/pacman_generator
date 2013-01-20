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

namespace PACMAN {
    namespace GENERATOR {

ChoiceTree::ChoiceTree(GameTree& tree, unsigned int max_choices)
:   tree(tree),
    max_choices(max_choices),
    choices_taken(0)
{
    INVARIANTS_ON_EXIT;
    tree.init(max_choices);
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
}

void ChoiceTree::init() {
    choices.reserve(max_choices*PLAYER_COUNT+1);
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
    return choices.back().action;
}

bool ChoiceTree::next_child() {
    INVARIANTS_ON_EXIT;
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
        vector<Action> actions;
        actions.reserve(PLAYER_COUNT);
        for (auto it = choices.end() - PLAYER_COUNT; it != choices.end(); it++) {
            actions.push_back((*it).action);
        }
        tree.child(actions);
    }

    choices.emplace_back(ChoiceNode{-1, (int)choices.size() % PLAYER_COUNT, -1});

    return true;
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
    int retval = tree.get_max_depth() * PLAYER_COUNT;
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

bool ChoiceTree::operator==(const ChoiceTree& other) const {
    return other.choices == choices;
}

void ChoiceTree::invariants() const {
    INVARIANT(!choices.empty());
    INVARIANT(choices_taken <= max_choices);
    INVARIANT(choices.size() > choices_taken);
    INVARIANT(choices.capacity() == max_choices*PLAYER_COUNT + 1);
}

}}
