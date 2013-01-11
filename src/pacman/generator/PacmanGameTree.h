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

            int init();
            void parent(const std::vector<ChoiceNode>& choices);
            int child(const std::vector<ChoiceNode>& choices);
            int get_child_count(const std::vector<ChoiceNode>& choices) const;
            int get_score() const;

        protected:
            void invariants() const;

        private:
            bool has_choice(const MODEL::GameState&, int player) const;
            int get_action(int player, const std::vector<ChoiceNode>& choices) const;
            int get_first_undecided(const MODEL::GameState&, int player) const;
            int progress_game_state(const std::vector<ChoiceNode>& choices);
            int progress_game_until_choice(MODEL::GameState& state);

            inline MODEL::GameState& get_state() {
                return states.back();
            }

            inline const MODEL::GameState& get_state() const {
                return states.back();
            }

        private:
            std::vector<MODEL::GameState> states;
            GUI::NullUIHints uihints;
            bool initialised; // true after call to ctor, false otherwise
        };

    }
}
