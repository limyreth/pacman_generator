/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "Input.h"
#include <pacman/model/IntermediateGameState.h>

#include <vector>
#include <memory>

namespace PACMAN {
    namespace RUN {

        class RecordedInput;
        typedef std::vector<std::shared_ptr<Input>> Inputs;

        // simplified interface to GameState succession, allowing to move in a certain direction as a certain player
        class Game
        {
        public:
            Game();
            void init(Inputs inputs);

            /*
             * Returns Inputs with input at player_index, and a ZeroInput at each other index
             */
            static Inputs make_inputs(int player_index, std::shared_ptr<Input> input);

            bool act(::PACMAN::MODEL::UIHints& uihints);
            const ::PACMAN::MODEL::GameState& get_state();
            void print_recorded_test(std::ostream&, RecordedInput&);
            int get_steps();
            void reset_steps();

        private:
            Inputs inputs;
            int steps;
            ::PACMAN::MODEL::IntermediateGameState state;
            bool initialised;
        };

    }
}
