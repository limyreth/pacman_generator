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
#include "../Point.h"

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

namespace PACMAN {
    namespace MODEL {

        class Nodes;
        class PacmanNodes;
        class GhostNodes;

        // these are choice nodes for pacman/ghosts
        class Node
        {
        public:
            Node(FPoint location);

            inline const FPoint& get_location() const {
                return location;
            }

            inline const std::vector<Node*>& get_neighbours() const {
                return neighbours;
            }

        private:
            FPoint location;
            std::vector<Node*> neighbours;

            friend Nodes;
            friend PacmanNodes;
            friend GhostNodes;
        };

    }
}
