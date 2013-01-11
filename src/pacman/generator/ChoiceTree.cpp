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

namespace PACMAN {

    namespace GENERATOR {

ChoiceTree::ChoiceTree(int max_depth, GameTree& tree) 
:   max_depth(max_depth), 
    tree(tree)
{
    REQUIRE(max_depth >= 0);
    INVARIANTS_ON_EXIT;
    choices.reserve(get_max_depth()+1);
    choices.emplace_back(ChoiceNode{-1, tree.init(), -1});
}

int ChoiceTree::parent() {
    INVARIANTS_ON_EXIT;
    tree.parent(choices);
    choices.pop_back();
    return choices.back().action;
}

bool ChoiceTree::next_child() {
    INVARIANTS_ON_EXIT;
    if (choices.back().action + 1 >= tree.get_child_count(choices)) {
        return false;
    }

    choices.back().action++;
    int player = tree.child(choices);
    choices.emplace_back(ChoiceNode{-1, player, -1});
    return true;
}

bool ChoiceTree::is_leaf() const {
    return choices.back().player == -1 || get_depth() == get_max_depth();
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
    return max_depth;
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

void ChoiceTree::invariants() const {
    INVARIANT(!choices.empty());
}

}}
