/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "../generator/GameTree.h"
#include "../model/Action.h"
#include <vector>

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

namespace PACMAN {

    namespace GENERATOR {
        struct ChoiceNode;
    }

    namespace TEST {

        struct TreeNode {
            int score;
            int player;
            shared_ptr<TreeNode> parent;
            std::vector<shared_ptr<TreeNode>> children;
        };

        class GameTree : public GENERATOR::GameTree
        {
        public:
            GameTree(shared_ptr<TreeNode> root) ;

            void parent();
            void child(const std::vector<MODEL::Action>& actions);
            MODEL::LegalActions get_legal_actions(int player) const;
            int get_score() const;
            bool is_leaf() const;

            inline int get_children_visited() {
                return children_visited;
            }

            void save(std::ostream& out) const;

        private:
            int children_visited; // if a child is visited twice, then it is counted twice = the number of calls to next_child that return true
            shared_ptr<TreeNode> node;  // curent node, starts as root
        };

    }
}
