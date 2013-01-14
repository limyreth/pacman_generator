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
#include "../util/assertion.h"

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
        class ChoiceTree : public ASSERTION::Assertable
        {
        public:
            ChoiceTree(int max_choice_rounds, GameTree& tree) ;

            /*
             * Move current node pointer to parent
             *
             * Returns action used to get to child that was the current node
             */
            virtual int parent();

            // move to next child, starting with the first child
            // Returns whether there actually was a child
            virtual bool next_child();

            // will calling next_child() return our first child?
            bool is_first_child() const;

            bool is_leaf() const;

            int get_score() const;
            int get_depth() const;  // current depth in the tree, depth is 0-based index
            int get_max_depth() const;  // inclusive max

            const GENERATOR::ChoiceNode& get() const;
            const GENERATOR::ChoiceNode& get(int depth) const;
            void set_alpha_beta(int alpha_beta);

            void save(std::ostream& out) const;

        protected:
            void invariants() const;

        private:
            const int max_depth;
            GameTree& tree;
            std::vector<GENERATOR::ChoiceNode> choices;  // 2D array of [round][player]
        };

    }
}
