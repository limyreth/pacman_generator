/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "ChoiceNode.h"
#include "../model/Action.h"

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

namespace PACMAN {

    namespace GENERATOR {

        class GameTree;

        /* A tree of choice nodes of a game of pacman
         *
         * A choice tree also keeps a list of ChoiceNodes. The last
         * ChoiceNode's action field is arbitrary/invalid; its player field
         * indicates the current player making a move.
         *
         * Every ChoiceNode has an alpha_beta value. It is not initialised,
         * ChoiceTree promises not to do anything with it.
         */
        class ChoiceTree
        {
        public:
            ChoiceTree(int max_depth, GameTree& tree) ;

            // move current node pointer to parent
            virtual void parent();

            // move to next child, starting with the first child
            // Returns whether there actually was a child
            virtual bool next_child();

            // will calling next_child() return our first child?
            bool is_first_child();

            bool is_leaf();

            int get_score();
            int get_depth();  // current depth in the tree, depth is 0-based index
            int get_max_depth();  // inclusive max

            const GENERATOR::ChoiceNode& get() const;
            const GENERATOR::ChoiceNode& get(int depth) const;
            void set_alpha_beta(int alpha_beta);

        private:
            int max_depth;
            GameTree& tree;
            std::vector<GENERATOR::ChoiceNode> choices;
        };

    }
}
