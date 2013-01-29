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

#include <vector>

namespace PACMAN {
    namespace MODEL {
        class ExternalGameState;
    }

    namespace TEST {
        void playback_test(const std::vector<MODEL::Action>& path, const ::PACMAN::MODEL::ExternalGameState& game_state, const int player_index, const int recorded_steps);
    }
}
