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
#include "../model/Action.h"

namespace PACMAN {

    namespace GENERATOR {

        struct ChoiceNode;

        /* 
         * A tree of game states, for a PLAYER_COUNT player game
         */
        class GameTree
        {
        public:

            virtual void init(unsigned int max_rounds) = 0;

            /*
             * Move to parent
             */
            virtual void parent() = 0;

            /* 
             * Move to child
             *
             * actions: size() == PLAYER_COUNT
             *
             * Returns false if game over
             */
            virtual void child(const std::vector<MODEL::Action>& actions) = 0;

            virtual unsigned char get_action_count(int player) const = 0;

            /*
             * score of current game state
             */
            virtual int get_score() const = 0;

            virtual bool is_leaf() const = 0;

            virtual void save(std::ostream& out) const = 0;

            /*
             * Get inclusive max depth (of subsequent rounds played)
             */
            virtual int get_max_depth() const = 0;
        };

    }
}
