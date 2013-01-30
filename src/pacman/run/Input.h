/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <pacman/model/Action.h>

namespace PACMAN {

    namespace MODEL {
        class IntermediateGameState;
    }

    namespace RUN {

        class Input
        {
        public:
            /*
             * Require: player_index's action_count > 0
             */
            virtual ::PACMAN::MODEL::Action get_action(int player_index, const ::PACMAN::MODEL::IntermediateGameState& state) = 0;
        };

    }
}
