/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "Constants.h"

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class GameState;

typedef char Action;
typedef Action Actions[ACTION_COUNT];

struct GameStateInfo {
    shared_ptr<GameState> state;
    Actions legal_actions[PLAYER_COUNT];  // legal_actions[player][action_index] player 0 is pacman, the next 4 are ghosts
};
