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

namespace PACMAN {
    namespace TEST {
        namespace MODEL {

            class GhostLeavingTests : public ::PACMAN::RUN::DefaultGameObserver {
            public:
                static void test_blinky_pinky_immediately_leave();
                static void test_dots_eaten();
            };

        }
    }
}
