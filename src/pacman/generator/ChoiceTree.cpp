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

using namespace ::PACMAN::MODEL;
using std::vector;

namespace PACMAN {
    namespace GENERATOR {

ChoiceTree::ChoiceTree(int max_choice_rounds, GameTree& tree) 
:   max_depth(max_choice_rounds*PLAYER_COUNT), 
    tree(tree)
{
    REQUIRE(max_depth >= 0);
    INVARIANTS_ON_EXIT;
    choices.reserve(get_max_depth()+1);
    choices.emplace_back(ChoiceNode{-1, 0, -1});
}

int ChoiceTree::parent() {
    INVARIANTS_ON_EXIT;
    choices.pop_back();
    if (choices.size() % PLAYER_COUNT == 0) {
        tree.parent();
    }
    return choices.back().action;
}

bool ChoiceTree::next_child() {
    INVARIANTS_ON_EXIT;
    auto legal_actions = tree.get_legal_actions(choices.back().player);
    if (choices.back().action == -1 && legal_actions.count == 0) {
        // repeat action of last round
        choices.back().action = (*(choices.rbegin()+PLAYER_COUNT)).action;
    }
    else if (choices.back().action + 1 < legal_actions.count) {
        choices.back().action++;
    }
    else {
        return false;
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
    return tree.is_leaf() || get_depth() == get_max_depth();
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
