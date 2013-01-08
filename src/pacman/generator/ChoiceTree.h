/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "../model/Action.h"

namespace PACMAN {

    namespace GENERATOR {

        struct ChoiceNode {
            // the move from this node to the next
            MODEL::Action action;  

            // index of player making the move
            int player;  

            // alpha or beta value. Depends on player.
            int alpha_beta;
        };

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
            // move current node pointer to parent
            virtual void parent() = 0;

            // move to next child, starting with the first child
            // Returns whether there actually was a child
            virtual bool next_child() = 0;

            // will calling next_child() return our first child?
            virtual bool is_first_child() = 0;

            virtual bool is_leaf() = 0;

            virtual int get_score() = 0;
            virtual int get_depth() = 0;  // current depth in the tree, depth is 0-based index
            virtual int get_max_depth() = 0;  // inclusive max

            virtual const ChoiceNode& get() const = 0;
            virtual const ChoiceNode& get(int depth) const = 0;
            virtual void set_alpha_beta(int alpha_beta) = 0;
        };

    }
}
