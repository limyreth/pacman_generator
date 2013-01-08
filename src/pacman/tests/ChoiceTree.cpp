/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "ChoiceTree.h"
#include "../util/assertion.h"

#include <iostream>

using std::cout;
using std::endl;
using PACMAN::GENERATOR::ChoiceNode;

namespace PACMAN {

    namespace TEST {

ChoiceTree::ChoiceTree(int max_depth, shared_ptr<TreeNode> root) 
:   max_depth(max_depth), 
    node(root),
    children_visited(0)
{
    choices.reserve(get_max_depth()+1);
    choices.emplace_back(ChoiceNode{-1, node->player, -1});
}

void ChoiceTree::parent() {
    cout << "parent" << endl;
    REQUIRE(node->parent != NULL);
    node = node->parent;
    choices.pop_back();
}

bool ChoiceTree::next_child() {
    choices.back().action++;
    if (choices.back().action >= node->children.size()) {
        cout << "end" << endl;
        return false;
    }
    else {
        node = node->children.at(choices.back().action);
        choices.emplace_back(ChoiceNode{-1, node->player, -1});

        ++children_visited;
        cout << "next child at " << get_depth() << ", value " << node->score << endl;
        return true;
    }
}

bool ChoiceTree::is_leaf() {
    return node->children.empty() || get_depth() == get_max_depth();
}

bool ChoiceTree::is_first_child() {
    REQUIRE(!is_leaf());
    return choices.back().action == -1;
}

int ChoiceTree::get_score() {
    return node->score;
}

int ChoiceTree::get_depth() {
    return choices.size()-1;
}

int ChoiceTree::get_max_depth() {
    return max_depth;
}

const GENERATOR::ChoiceNode& ChoiceTree::get() const {
    return choices.back();
}

const GENERATOR::ChoiceNode& ChoiceTree::get(int depth) const {
    return choices.at(depth);
}

void ChoiceTree::set_alpha_beta(int alpha_beta) {
    choices.back().alpha_beta = alpha_beta;
}

}}
