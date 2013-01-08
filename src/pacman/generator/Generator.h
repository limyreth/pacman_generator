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

namespace PACMAN {

    namespace GENERATOR {

        class Generator
        {
        public:
            Generator(ChoiceTree& tree);
            void run(int& best_score);

        private:
            void invariants();
            int get_alpha() const;
            int get_alpha(int depth) const;
            int get_beta() const;
            int get_beta(int depth) const;
            void push_alpha_beta();
            void pop_alpha_beta();

            int translate(int i) const;

            void minimax();

        private:
            ChoiceTree& choice_tree;
        };

    }
}