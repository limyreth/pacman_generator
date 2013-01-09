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

        struct TreeNode {
            int score;
            int player;
            shared_ptr<TreeNode> parent;
            std::vector<shared_ptr<TreeNode>> children;
        };

        class ChoiceTree : public GENERATOR::ChoiceTree
        {
        public:
            ChoiceTree(int max_depth, shared_ptr<TreeNode> root) ;

            void parent();
            bool next_child();
            bool is_leaf();
            bool is_first_child();

            int get_score();
            int get_depth();
            int get_max_depth();

            const GENERATOR::ChoiceNode& get() const;
            const GENERATOR::ChoiceNode& get(int depth) const;
            void set_alpha_beta(int alpha_beta);

            inline int get_children_visited() {
                return children_visited;
            }

        private:
            int max_depth;
            int children_visited; // if a child is visited twice, then it is counted twice = the number of calls to next_child that return true
            shared_ptr<TreeNode> node;  // curent node, starts as root
            std::vector<GENERATOR::ChoiceNode> choices;
        };

    }
}
