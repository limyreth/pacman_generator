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

ChoiceTree::ChoiceTree(int max_depth, GENERATOR::GameTree& tree) 
:   GENERATOR::ChoiceTree(max_depth, tree),
    children_visited(0)
{
}

int ChoiceTree::parent() {
    cout << "parent" << endl;
    GENERATOR::ChoiceTree::parent();
}

bool ChoiceTree::next_child() {
    bool had_child = GENERATOR::ChoiceTree::next_child();
    if (had_child) {
        ++children_visited;
        cout << "next child at " << get_depth() << ", value " << get_score() << endl;
    }
    else {
        cout << "end" << endl;
    }
    return had_child;
}

}}
