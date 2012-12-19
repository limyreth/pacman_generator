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

Game::Game(const int* walls)
{
    game_state_info = GameState::start_new_game(pacman_nodes.init(walls), ghost_nodes.init(walls));
}

void Game::logicGame(shared_ptr<UIHints> uihints) {
    if (get_state()->did_pacman_win() || get_state()->did_pacman_lose()) {
        assert(false); // TODO implement proper reaction to this
    }

    Action actions[PLAYER_COUNT] = {-1, -1, -1, -1, -1};
    for (int i=0; i<PLAYER_COUNT; ++i) {
        for (int j=0; j<4; ++j) {
            Action action = game_state_info.legal_actions[i][j];
            if (action > -1) {
                actions[i] = action;
                break;
            }
        }
    }
    game_state_info = get_state()->get_successor(actions, *uihints);
}

void Game::processLogic(shared_ptr<UIHints> uihints) {
    // TODO rm intermediate
    logicGame(uihints);
}

