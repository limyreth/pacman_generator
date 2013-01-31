/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "playback_test.h"
#include <pacman/model/GameState.h>
#include <pacman/run/PlaybackInput.h>
#include <pacman/test/model/PathTest.h>

#include <memory>

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;

using namespace ::PACMAN::MODEL;
using namespace ::PACMAN::RUN;

namespace PACMAN {
    namespace TEST {

void playback_test(const std::vector<Action>& path, const ExternalGameState& expected_state, const int player_index, const int recorded_steps) {
    ::PACMAN::TEST::MODEL::PathTest test(player_index, path);
    auto state = test.run(recorded_steps);
    ASSERT(state.is_equivalent_to(expected_state));
}

}}
