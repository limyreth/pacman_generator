/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "ChoiceTree.h"
#include "../util/assertion.h"

namespace PACMAN {

    namespace GENERATOR {

        /* 
         * REQUIRE(provided ChoiceTree's score increases (non-strictly) when depth increases)
         *
         * Background info:
         *
         * We use minimax with alpha beta pruning. Pruning leads to
         * O(b**(3d/4)) execution time instead of O(b**d), assuming we have a
         * random ordering.
         *
         * Negascout might work even better... or might not even work at all.
         *
         * Or we could improve the ordering...
         */
        class Generator : public ASSERTION::Assertable
        {
        public:
            Generator(ChoiceTree& tree);
            Generator(std::istream& in, ChoiceTree& tree);
            void save(std::ostream& out) const;
            bool operator==(const Generator&) const;
            int get_best_score() const;

            /*
             * Each path can be fed to a PlaybackInput for the corresponding player
             * (i.e. it contains an Action for each time this player has to
             * act, has an action count > 0)
             */
            std::vector<std::vector<MODEL::Action>> get_best_player_paths() const;

            void run(); 
            void stop(); // you can call this from another thread to stop a run

        protected:
            void invariants() const;

        private:
            int get_alpha() const;
            int get_alpha(int depth) const;
            int get_beta() const;
            int get_beta(int depth) const;
            void print_completion() const;

            void minimax();


        private:
            bool is_running;
            bool should_stop;

            ChoiceTree& choice_tree;
            std::vector<std::vector<MODEL::Action>> paths;
            int child_value;
            int child_action; // the action used to get to the child we just examined
            bool search_complete;
        };

    }
}
