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
#include "../model/IntermediateGameState.h"
#include "../model/NullGameStateObserver.h"
#include "../util/assertion.h"

namespace PACMAN {

    namespace GENERATOR {

        class PacmanGameTree : public GameTree, public ASSERTION::Assertable
        {
        public:
            PacmanGameTree();

            void init(unsigned int max_rounds);
            void parent();
            void child(const std::vector<MODEL::Action>& actions);
            unsigned char get_action_count(int player) const;
            int get_score() const;
            bool is_leaf() const;
            bool is_root() const;

            bool operator==(const GameTree&) const;

        protected:
            void invariants() const;

        private:
            bool generate_actions(const MODEL::IntermediateGameState& state, std::vector<MODEL::Action>& actions) const;
            void progress_game_until_choice(MODEL::IntermediateGameState& state);

        private:
            std::vector<MODEL::IntermediateGameState> states;
            MODEL::NullGameStateObserver state_observer;
            unsigned int max_depth;
            bool initialised;
        };

    }
}
