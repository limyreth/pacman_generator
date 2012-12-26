/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "model/GameStateInfo.h"
#include "model/PacmanNodes.h"
#include "model/GhostNodes.h"

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

namespace PACMAN {

    namespace MODEL {
        class GameState;
        class UIHints;
    }

    class Game
    {
    public:
        Game();

        void step(const MODEL::Action* actions, shared_ptr<MODEL::UIHints> uihints);

        inline shared_ptr<MODEL::GameState> get_state() const {
            return state;
        }

        inline const MODEL::PacmanNodes& get_pacman_nodes() const {
            return pacman_nodes;
        }

        inline const MODEL::GhostNodes& get_ghost_nodes() const {
            return ghost_nodes;
        }

    private:
        shared_ptr<MODEL::GameState> state;
        MODEL::PacmanNodes pacman_nodes;
        MODEL::GhostNodes ghost_nodes;
    };

}
