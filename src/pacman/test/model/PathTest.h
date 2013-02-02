/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <pacman/run/DefaultGameObserver.h>
#include <pacman/model/Action.h>

#include <vector>

namespace PACMAN {

    namespace MODEL {
        class GameState;
    }

    namespace TEST {
        namespace MODEL {

            class PathTest : public ::PACMAN::RUN::DefaultGameObserver {
            public:
                PathTest(std::vector<std::vector< ::PACMAN::MODEL::Action>>& paths);
                PathTest(int player_index, const std::vector< ::PACMAN::MODEL::Action>& path);
                PathTest(const std::vector< ::PACMAN::MODEL::Action>& path);

                ::PACMAN::MODEL::GameState run(int stop_at_step);
            };

        }
    }
}
