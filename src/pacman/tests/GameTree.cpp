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
using PACMAN::GENERATOR::ChoiceNode;

namespace PACMAN {
    namespace TEST {

GameTree::GameTree(shared_ptr<TreeNode> root) 
:   node(root),
    children_visited(0)
{
}

void GameTree::parent() {
    REQUIRE(node->parent != NULL);
    node = node->parent;
}

void GameTree::child(const std::vector<MODEL::Action>& actions) {
    REQUIRE(actions.size() == PLAYER_COUNT);
    for (int player=0; player < PLAYER_COUNT; ++player) {
        REQUIRE(actions.at(player) < get_legal_actions(player).count);
    }

    node = node->children.at(actions.at(node->player));
    ++children_visited;
}

MODEL::LegalActions GameTree::get_legal_actions(int player) const {
    MODEL::LegalActions legal_actions;
    legal_actions.reverse_action = -1;

    if (node->player == player) {
        legal_actions.count = node->children.size();
    } else {
        legal_actions.count = 1;
    }

    return legal_actions;
}

int GameTree::get_score() const {
    return node->score;
}

bool GameTree::is_leaf() const {
    return node->children.empty();
}

void GameTree::save(std::ostream& out) const {
    REQUIRE(false);
}

}}
