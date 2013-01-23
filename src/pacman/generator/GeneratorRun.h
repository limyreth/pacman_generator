/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "../generator/Generator.h"
#include "../generator/PacmanGameTree.h"
#include "../generator/ChoiceTree.h"

namespace PACMAN {
    namespace GENERATOR {

        // a run generating pacman perfect solution
        class GeneratorRun
        {
        public:
            GeneratorRun();
            GeneratorRun(std::istream& in);
            void stop();
            void join(std::ostream& out);
            bool operator==(const GeneratorRun&) const;

        private:
            PacmanGameTree game_tree;
            ChoiceTree choice_tree;
            Generator generator;
        };

    }
}
