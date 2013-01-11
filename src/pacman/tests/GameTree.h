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

            int init();
            void parent(const std::vector<GENERATOR::ChoiceNode>& choices);
            int child(const std::vector<GENERATOR::ChoiceNode>& choices);
            int get_child_count(const std::vector<GENERATOR::ChoiceNode>& choices) const;
            int get_score() const;

        private:
            shared_ptr<TreeNode> node;  // curent node, starts as root
        };

    }
}
