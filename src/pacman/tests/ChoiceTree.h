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

        // a tree of choice nodes of a game of pacman
        class ChoiceTree : public GENERATOR::ChoiceTree
        {
        public:
            ChoiceTree(int max_depth, shared_ptr<TreeNode> root) ;

            void parent();
            bool next_sibling();
            void first_child();
            bool is_leaf();

            int get_score();
            int get_max_depth();

            const GENERATOR::ChoiceNode& get() const;
            const GENERATOR::ChoiceNode& get(int depth) const;

        private:
            int max_depth;
            shared_ptr<TreeNode> node;  // curent node, starts as root
            std::vector<GENERATOR::ChoiceNode> choices;
        };

    }
}
