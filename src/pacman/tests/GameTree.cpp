/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "GameTree.h"
#include "../generator/ChoiceNode.h"
#include "../util/assertion.h"

#include <iostream>

using std::cout;
using std::endl;
using PACMAN::GENERATOR::ChoiceNode;

namespace PACMAN {

    namespace TEST {

GameTree::GameTree(shared_ptr<TreeNode> root) 
:   node(root)
{
}

int GameTree::init() {
    return node->player;
}

void GameTree::parent(const std::vector<ChoiceNode>& choices) {
    REQUIRE(node->parent != NULL);
    node = node->parent;
}

int GameTree::child(const std::vector<ChoiceNode>& choices) {
    node = node->children.at(choices.back().action);
    return node->player;
}

int GameTree::get_child_count(const std::vector<ChoiceNode>& choices) {
    return node->children.size();
}

int GameTree::get_score() {
    return node->score;
}

}}
