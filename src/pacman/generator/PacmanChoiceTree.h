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
#include "../model/Action.h"
#include "../model/GameState.h"
#include "../gui/NullUIHints.h"

namespace PACMAN {

    namespace GENERATOR {

        // a tree of choice nodes of a game of pacman
        class PacmanChoiceTree : public ChoiceTree
        {
        public:
            PacmanChoiceTree();

            void parent();
            bool next_sibling();
            void first_child();
            bool is_leaf();

            int get_score();
            int get_max_depth();

            const ChoiceNode& get() const;
            const ChoiceNode& get(int depth) const;

        private:
            void invariants();
            bool has_choice(int player) const;
            int get_first_undecided(int player) const;
            int progress_game_state();
            int progress_game_until_choice(MODEL::GameState& state);
            void push_choice(int next_player);

            // Note: never overload with different accessibility http://stackoverflow.com/questions/1361618/const-overloading-public-private-lookup-in-c-class
            inline ChoiceNode& get_() {
                return choices.back();
            }

            inline MODEL::GameState& get_state() {
                return states.at(state_index);
            }

            inline const MODEL::GameState& get_state() const {
                return states.at(state_index);
            }

        private:
            std::vector<ChoiceNode> choices;
            int depth;  // starts at max, then counts down. Is choice index

            std::vector<MODEL::GameState> states;  // Note: this is probably too much as sometimes multiple players need to move at the same time in the same tick
            int state_index; // starts at max, then counts down

            GUI::NullUIHints uihints;

            bool initialised; // true after call to ctor, false otherwise
            bool search_complete;
        };

    }
}
