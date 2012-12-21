/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Game.h"
#include "GameState.h"
#include "Constants.h"

// debug
using std::cout;
using std::endl;

Game::Game()
{
    state = GameState::start_new_game(pacman_nodes.init(), ghost_nodes.init());
}

void Game::step(shared_ptr<UIHints> uihints) {
    if (get_state()->did_pacman_win() || get_state()->did_pacman_lose()) {
        assert(false); // TODO implement proper reaction to this
    }

    Action actions[PLAYER_COUNT] = {0, 0, 0, 0, 0};
    state = get_state()->get_successor(actions, *uihints);
}

