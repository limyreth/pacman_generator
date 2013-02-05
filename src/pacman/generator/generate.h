/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "ChoiceTree.h"
#include "../util/assertion.h"
#include "GeneratorRun.h"

#include <memory>

namespace PACMAN {

    namespace GENERATOR {

        class GeneratorMain {
        public:
            GeneratorMain(const std::string STATE_DIR, unsigned int max_choices);
            void run();

        private:
            static void signal_callback(int signum);
            int find_previous_state();
            std::string get_state_path(int number);
            void stop();

        private:
            std::shared_ptr<GeneratorRun> generator;
            const std::string STATE_DIR;
            int previous_state_number;
            unsigned int max_choices;
        };

    }
}
