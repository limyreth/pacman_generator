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
#include "../Constants.h"

#include <iostream>

using std::cout;
using std::endl;
using std::shared_ptr;
using PACMAN::GENERATOR::ChoiceNode;

namespace PACMAN {
    namespace TEST {

GameTree::GameTree(shared_ptr<TreeNode> root) 
:   node(root),
    children_visited(0)
{
}

void GameTree::init(unsigned int max_rounds) {
    max_depth = max_rounds;
}

void GameTree::parent() {
    REQUIRE(node->parent != NULL);
    node = node->parent;
}

void GameTree::child(const std::vector<MODEL::Action>& actions) {
    REQUIRE(actions.size() == PLAYER_COUNT);
    for (int player=0; player < PLAYER_COUNT; ++player) {
        REQUIRE(actions.at(player) < get_action_count(player));
    }

    node = node->children.at(actions.at(node->player));
    ++children_visited;
}

unsigned char GameTree::get_action_count(int player) const {
    if (node->player == player) {
        return node->children.size();
    } else {
        return 1;
    }
}

int GameTree::get_score() const {
    return node->score;
}

bool GameTree::is_leaf() const {
    return node->children.empty();
}

int GameTree::get_max_depth() const {
    return max_depth;
}

}}
