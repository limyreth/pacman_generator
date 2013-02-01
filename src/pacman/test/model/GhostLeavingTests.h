/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

namespace PACMAN {
    namespace TEST {
        namespace MODEL {

            class GhostLeavingTests {
            public:
                static void test_blinky_pinky_immediately_leave();
                static void test_dots_eaten();
                static void test_time();
            };

        }
    }
}
