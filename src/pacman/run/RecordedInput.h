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

#include <list>
#include <memory>

namespace PACMAN {
    namespace RUN {

        /*
         * Record input returned
         */
        class RecordedInput : public Input
        {
        public:
            RecordedInput(Input& input);

            ::PACMAN::MODEL::Action get_action(int player_index, const ::PACMAN::MODEL::IntermediateGameState& state);
            void print_path(std::ostream&);

        private:
            Input& input;
            std::list< ::PACMAN::MODEL::Action> path;
        };

    }
}