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

namespace PACMAN {

    namespace TEST {

ChoiceTree::ChoiceTree(int max_depth, shared_ptr<TreeNode> root) 
:   max_depth(max_depth), 
    node(root)
{
}

void ChoiceTree::parent() {
    REQUIRE(node->parent != NULL);
    node = node->parent;
    choices.pop_back();
}

bool ChoiceTree::next_sibling() {
    auto siblings = node->parent->children;
    auto it = std::find(siblings.begin(), siblings.end(), node);
    ASSERT(it != siblings.end());
    it++;
    if (it == siblings.end()) {
        return false;
    }
    else {
        node = *it;
        choices.back().action++;
        choices.back().player = node->player;
        return true;
    }
}

void ChoiceTree::first_child() {
    node = node->children.front();
    choices.emplace_back(GENERATOR::ChoiceNode {0, node->player});
}

bool ChoiceTree::is_leaf() {
    return node->children.empty();
}

int ChoiceTree::get_score() {
    return node->score;
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

}}
