/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "GameStateInfo.h"
#include "PacmanNodes.h"
#include "GhostNodes.h"

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class GameState;
class UIHints;

class Game
{
public:
    Game();

    void step(shared_ptr<UIHints> uihints);

    inline shared_ptr<GameState> get_state() const {
        return game_state_info.state;
    }

    inline const PacmanNodes& get_pacman_nodes() const {
        return pacman_nodes;
    }

    inline const GhostNodes& get_ghost_nodes() const {
        return ghost_nodes;
    }

private:
    GameStateInfo game_state_info;

    PacmanNodes pacman_nodes;
    GhostNodes ghost_nodes;
};
