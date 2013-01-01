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
#include "model/GameState.h"

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

namespace PACMAN {

    namespace MODEL {
        class UIHints;
    }

    class Game
    {
    public:
        Game();

        void step(const MODEL::Action* actions, shared_ptr<MODEL::UIHints> uihints);

        inline MODEL::GameState* get_state() {
            return &state;
        }

    private:
        MODEL::GameState state;
    };

}
