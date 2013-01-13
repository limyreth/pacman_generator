/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "GameTree.h"
#include "../model/Action.h"
#include "../model/GameState.h"
#include "../gui/NullUIHints.h"
#include "../util/assertion.h"

namespace PACMAN {

    namespace GENERATOR {

        /* 
         * Quite like a ChoiceTree, but doesn't keep track of choices made
         */
        class PacmanGameTree : public GameTree, public ASSERTION::Assertable
        {
        public:
            PacmanGameTree(int max_depth);

            void parent();
            void child(const std::vector<MODEL::Action>& actions);
            MODEL::LegalActions get_legal_actions(int player) const;
            int get_score() const;
            bool is_leaf() const;

        protected:
            void invariants() const;

        private:
            bool generate_actions(const MODEL::GameState& state, MODEL::Action* prev_actions, MODEL::Action* actions);
            void progress_game_until_choice(MODEL::GameState& state, MODEL::Action* prev_actions);

        private:
            std::vector<MODEL::GameState> states;
            GUI::NullUIHints uihints;

            // used solely for assertions
            const int max_depth;
        };

    }
}
