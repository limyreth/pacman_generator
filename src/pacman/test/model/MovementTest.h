/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <pacman/util/Directions.h>
#include <pacman/run/Game.h>
#include <pacman/run/DefaultGameObserver.h>
#include <pacman/run/DirectionPreference.h>
#include <pacman/model/Action.h>

#include <memory>

namespace PACMAN {

    namespace MODEL {
        class GameState;
        class NullUIHints;
    }

    namespace TEST {
        namespace MODEL {

            class MovementTest : public RUN::DirectionPreference, public RUN::DefaultGameObserver {
            public:
                MovementTest(int player_index);
                int move(Direction::Type direction);
                const ::PACMAN::MODEL::GameState& get_state();
                Direction::Type get_preferred_direction();

                void finished_step(const ::PACMAN::MODEL::GameState& state);
                bool should_stop();

            private:
                Direction::Type current_direction;
                int player_index;
                ::PACMAN::MODEL::GameState original;
            };

        }
    }
}
