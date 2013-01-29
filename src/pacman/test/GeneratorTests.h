/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <sstream>
#include <memory>

namespace PACMAN {

    namespace GENERATOR {
        class GeneratorRun;
    }

    namespace TEST {

        // test entire generator subsystem
        class GeneratorTests {
        public:
            static void test_1();
            static void test_save_load();
            static void test_save_load_of_running_instance();
        };

        class SaveLoadRunningGeneratorTest {
        public:
            void test();

        private:
            void thread_callback();

        private:
            std::shared_ptr<GENERATOR::GeneratorRun> run;
            std::stringstream str;
        };

    }
}
