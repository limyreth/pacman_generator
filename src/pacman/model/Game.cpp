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

using std::cout;
using std::endl;
using std::vector;

namespace PACMAN {
    namespace MODEL {

Game::Game(int player_index)
:   state(IntermediateGameState::new_game()),
    player_index(player_index)
{
    REQUIRE(player_index >= 0);
    REQUIRE(player_index < PLAYER_COUNT);
}

/*
 * Returns true when get_state() changed
 */
bool Game::act(Direction::Type direction, UIHints& uihints) {
    vector<Action> actions(PLAYER_COUNT, 0);
    auto old_state = get_state();

    if (state.get_action_count(player_index) > 0) {
        actions.at(player_index) = state.get_action_along_direction(player_index, direction);
        path.push_back(actions.at(player_index));
    }

    state = state.act(actions, uihints);

    return old_state != get_state();
}

const MODEL::GameState& Game::get_state() {
    return state.get_predecessor();
}

void Game::print_path() {
    cout << "{";
    for (auto action : path) {
        cout << (int)action << ", ";
    }
    cout << "}" << endl;
}

}}
