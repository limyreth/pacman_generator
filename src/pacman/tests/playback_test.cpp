/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "playback_test.h"
#include "../model/NullUIHints.h"
#include "../model/IntermediateGameState.h"

using std::cout;
using std::endl;
using std::vector;

using namespace ::PACMAN::MODEL;

namespace PACMAN {
    namespace TEST {

void playback_test(const std::vector<Action>& path, const GameState& game_state, const int player_index, const int recorded_steps) {
    NullUIHints uihints;
    auto current_action = path.begin();
    IntermediateGameState state = IntermediateGameState::new_game();
    vector<Action> actions(PLAYER_COUNT, 0);
    int steps = 0;

    while (recorded_steps != steps) {
        if (state.get_action_count(player_index) > 0) {
            actions.at(player_index) = *current_action;
            current_action++;
        }

        auto old_state = state.get_predecessor();
        state = state.act(actions, uihints);

        if (old_state != state.get_predecessor()) {
            steps++;
        }
    }

    ASSERT(current_action == path.end());
    ASSERT(state.get_predecessor() == game_state);
}

}}
