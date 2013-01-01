/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <vector>
#include "Nodes.h"

namespace PACMAN {
    namespace MODEL {

        // these are choice nodes for pacman/ghosts
        class GhostNodes : public Nodes
        {
        public:
            GhostNodes();
            ~GhostNodes();

            const std::vector<Node*> get_spawns() const {
                return spawns;
            }

        private:
            std::vector<Node*> spawns;
        };

        extern const GhostNodes GHOST_NODES;

    }
}
