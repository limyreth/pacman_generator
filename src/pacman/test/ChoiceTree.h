/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "../generator/ChoiceTree.h"
#include "../model/Action.h"

#include <list>

namespace PACMAN {
    namespace TEST {

        class ChoiceTree : public GENERATOR::ChoiceTree
        {
        public:
            ChoiceTree(GENERATOR::GameTree& tree, unsigned int max_choices) ;

            int parent();
            bool next_child();
        };

    }
}
