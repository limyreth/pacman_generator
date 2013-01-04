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
#include "../gui/NullUIHints.h"

namespace PACMAN {
    namespace MODEL {
        class GameState;
    }

    namespace GENERATOR {

        void generate();

        // TODO make private
        struct ChoiceNode {
            // if is_pacman, then this is alpha, else it is beta value of current search tree node
            // alpha ~= highest score pacman can get
            // beta ~= lowest score ghost can make pacman get
            int alpha_beta; 

            // action taken to get from this state to the next
            MODEL::Action action;  

            // index of player making the move
            int player;  
        };


        class Generator
        {
        public:
            Generator();
            void run();

        private:
            void invariants();
            int get_alpha() const;
            int get_beta() const;
            bool has_choice(int player) const;
            int get_first_undecided(int player) const;
            int progress_game_state();
            int progress_game_until_choice(MODEL::GameState& state);
            void push_child(int next_player);
            void pop();

            int minimax();

            inline ChoiceNode& get() {
                return choices.at(choice_index);
            }

            inline const ChoiceNode& get() const {
                return get(choice_index);
            }

            inline const ChoiceNode& get(int depth) const {
                return choices.at(choice_index);
            }

            inline MODEL::GameState& get_state() {
                return states.at(state_index);
            }

            inline const MODEL::GameState& get_state() const {
                return states.at(state_index);
            }

        private:
            std::vector<ChoiceNode> choices;
            int choice_index;  // starts at max, then counts down. Is choice index

            std::vector<MODEL::GameState> states;  // Note: this is probably too much as sometimes multiple players need to move at the same time in the same tick
            int state_index; // starts at max, then counts down

            GUI::NullUIHints uihints;

            bool initialised; // true after call to ctor, false otherwise
            bool search_complete;
        };

    }
}
