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
#include <pacman/model/Action.h>

#include <vector>

namespace PACMAN {
    namespace RUN {

        /*
         * Input that is play backed (using a path)
         */
        class PlaybackInput : public Input
        {
        public:
            PlaybackInput(const std::vector< ::PACMAN::MODEL::Action>& path);

            bool has_more();
            ::PACMAN::MODEL::Action get_action(int player_index, const ::PACMAN::MODEL::IntermediateGameState& state);
            void print_path(std::ostream&);

        private:
            std::vector< ::PACMAN::MODEL::Action> path;
            std::vector< ::PACMAN::MODEL::Action>::iterator current_action;
        };

    }
}
