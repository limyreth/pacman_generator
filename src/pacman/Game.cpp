/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Game.h"
#include "model/GameState.h"
#include "Constants.h"

namespace PACMAN {

using namespace MODEL;

// debug
using std::cout;
using std::endl;

Game::Game()
{
    state = GameState(pacman_nodes.get_spawn(), ghost_nodes.init());
}

void Game::step(const Action* actions, shared_ptr<UIHints> uihints) {
    if (get_state()->did_pacman_win() || get_state()->did_pacman_lose()) {
        assert(false); // TODO implement proper reaction to this
    }

    GameState successor(actions, &state, *uihints);
    state = successor;
}

}
