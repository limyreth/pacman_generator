/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "../generator/ChoiceTree.h"
#include "../model/Action.h"

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

namespace PACMAN {

    namespace TEST {

        class ChoiceTree : public GENERATOR::ChoiceTree
        {
        public:
            ChoiceTree(int max_depth, GENERATOR::GameTree& tree) ;

            int parent();
            bool next_child();

            inline int get_children_visited() {
                return children_visited;
            }

        private:
            int children_visited; // if a child is visited twice, then it is counted twice = the number of calls to next_child that return true
        };

    }
}
