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
            // action taken to get from this state to the next
            MODEL::Action action;  

            // index of player making the move
            int player;  
        };

        // a tree of choice nodes
        class ChoiceTree
        {
        public:
            // move current node pointer to parent
            virtual void parent() = 0;

            // move to next sibling
            // Returns whether there actually was a sibling
            virtual bool next_sibling() = 0;

            // move to first child
            virtual void first_child() = 0;

            virtual bool is_leaf() = 0;

            virtual int get_score() = 0;
            virtual int get_max_depth() = 0;  // depth is 0-based index, max is inclusive

            virtual const ChoiceNode& get() const = 0;
            virtual const ChoiceNode& get(int depth) = 0;
        };

    }
}
