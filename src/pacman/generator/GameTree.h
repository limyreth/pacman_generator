/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <vector>

namespace PACMAN {

    namespace GENERATOR {

        struct ChoiceNode;

        /* Quite like a ChoiceTree, but doesn't keep track of choices made
         */
        class GameTree
        {
        public:
            /*
             * Initialise
             *
             * Returns player who has to make a choice
             */
            virtual int init() = 0;

            /*
             * Move to parent
             */
            virtual void parent(const std::vector<ChoiceNode>& choices) = 0;

            /* 
             * Move to children[choices.back().action]
             *
             * choices = a path of choices to get to the child. I.e. back() is
             * currently made choice, other elements are previous choices.
             *
             * Returns the player who has to make a choice, or -1 if game over
             */
            virtual int child(const std::vector<ChoiceNode>& choices) = 0;

            virtual int get_child_count(const std::vector<ChoiceNode>& choices) const = 0;

            // score of current game state
            virtual int get_score() const = 0;
        };

    }
}
