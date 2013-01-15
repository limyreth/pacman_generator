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

ChoiceTree::ChoiceTree(GameTree& tree) 
:   tree(tree)
{
    INVARIANTS_ON_EXIT;
    choices.reserve(get_max_depth()+1);
    choices.emplace_back(ChoiceNode{-1, 0, -1});
}

ChoiceTree::ChoiceTree(std::istream& in, GameTree& tree)
:   tree(tree)
{
    INVARIANTS_ON_EXIT;
    choices.reserve(get_max_depth()+1);

    vector<ChoiceNode>::size_type size;
    read(in, size);
    choices.resize(size);

    in.read((char*)choices.data(), choices.size() * sizeof(ChoiceNode));
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
    write(out, choices.size());
    out.write((const char*)choices.data(), choices.size() * sizeof(ChoiceNode));
}

bool ChoiceTree::operator==(const ChoiceTree& other) const {
    return other.choices == choices;
}

void ChoiceTree::invariants() const {
    INVARIANT(!choices.empty());
    INVARIANT(choices.capacity() == get_max_depth() + 1);
}

}}
