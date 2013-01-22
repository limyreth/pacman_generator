/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

//////////////////////////////////////////////////////
// Pacman version 4
// Started September 5, 2008
// using C++ & SDL
// ported to linux with attempt at crossplatform compatibility
//////////////////////////////////////////////////////

#include "Game.h"
#include "../Constants.h"

using std::vector;

namespace PACMAN {
    namespace MODEL {

Game::Game(int player_index)
:   state(IntermediateGameState::new_game()),
    player_index(player_index)
{
    current = get_state();
}

/*
 * Returns true when get_state() changed
 */
bool Game::act(Direction::Type direction, UIHints& uihints) {
    vector<Action> actions(PLAYER_COUNT, 0);

    if (state.get_action_count(player_index) > 0) {
        actions.at(player_index) = state.get_action_along_direction(player_index, direction);
    }

    state = state.act(actions, uihints);
    if (current != get_state()) {
        current = get_state();
        return true;
    }

    return false;
}

const MODEL::GameState& Game::get_state() {
    return state.get_predecessor();
}

}}
