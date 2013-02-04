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

ChoiceTree::ChoiceTree(GENERATOR::GameTree& tree, unsigned int max_choices)
:   GENERATOR::ChoiceTree(tree, max_choices)
{
}

int ChoiceTree::parent() {
    cout << "parent" << endl;
    return GENERATOR::ChoiceTree::parent();
}

bool ChoiceTree::next_child() {
    bool had_child = GENERATOR::ChoiceTree::next_child();
    if (had_child) {
        cout << "next child at " << get_depth()/5.0 << ", value " << get_score() << endl;
    }
    else {
        cout << "end" << endl;
    }
    return had_child;
}

}}
