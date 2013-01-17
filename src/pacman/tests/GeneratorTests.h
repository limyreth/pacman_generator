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

        // test entire generator subsystem
        class GeneratorTests {
        public:
            static void test_1();
            static void test_save_load();
            static void test_save_load_of_running_instance();
        };

    }
}