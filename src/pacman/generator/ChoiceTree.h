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

#include <vector>

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
            ChoiceTree(GameTree& tree, unsigned int max_choices);
            ChoiceTree(std::istream& in, GameTree& tree);
            virtual ~ChoiceTree() {}

            /*
             * Move current node pointer to parent
             *
             * Returns action used to get to child that was the current node.
             * This action is >=PLAYER_COUNT if there was no choice for the
             * corresponding player.
             */
            virtual ::PACMAN::MODEL::Action parent();

            // move to next child, starting with the first child
            // Returns whether there actually was a child
            virtual bool next_child();

            // will calling next_child() return our first child?
            bool is_first_child() const;

            bool is_leaf() const;

            // get index of player making the move at given depth
            unsigned int get_player(unsigned int depth) const;

            int get_score() const;
            unsigned int get_depth() const;  // current depth in the tree, depth is 0-based index
            unsigned int get_max_depth() const;  // inclusive max
            double get_completion() const;

            const GENERATOR::ChoiceNode& get() const;
            const GENERATOR::ChoiceNode& get(int depth) const;
            void set_alpha_beta(int alpha_beta);

            void save(std::ostream& out) const;

            bool operator==(const ChoiceTree&) const;

        protected:
            void invariants() const;

        private:
            void restore_game_tree() const;
            virtual void init();
            void enter_child(std::vector<ChoiceNode>::const_iterator& it) const;

        private:
            unsigned int max_choices;
            unsigned int choices_taken; // choices taken along current choice path
            GameTree& tree;
            std::vector<GENERATOR::ChoiceNode> choices;  // 2D array of [round][player]
        };

    }
}
