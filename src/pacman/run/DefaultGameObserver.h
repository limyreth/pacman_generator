/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "GameObserver.h"
#include <pacman/run/Game.h>

#include <memory>

namespace PACMAN {
    namespace RUN {

        class Game;
        class Input;

        class DefaultGameObserver : public GameObserver
        {
        public:
            DefaultGameObserver(int player_index, std::shared_ptr<Input> input);

            void finished_step(const ::PACMAN::MODEL::GameState& state);
            bool should_stop();
            bool is_paused();
            void pause();

        protected:
            Game game;
        };

    }
}
