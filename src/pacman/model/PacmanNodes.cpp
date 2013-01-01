/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "PacmanNodes.h"
#include "Node.h"
#include "../Utility.h"
#include "../Constants.h"
#include "../specification/Walls.h"

using std::vector;
using std::cout;
using std::endl;

namespace PACMAN {
    namespace MODEL {

using SPECIFICATION::walls;

PacmanNodes::PacmanNodes() {
    Nodes::init();
    for (int x=0; x < MAP_WIDTH; ++x) {
        for (int y=0; y < MAP_HEIGHT; ++y) {
            auto& node = nodes.at(at(x, y));
            if (!node)
                continue; 
            // if we are intersection/corner
            if ((walls[at_wrap(x-1,y)] == 0 || walls[at_wrap(x+1,y)] == 0)  // a free tile along x-axis
                    && (walls[at(x, y-1)] == 0 || walls[at(x, y+1)]) == 0)  // and a free tile along the y-axis
            {
                assert(node->neighbours.size() >= 2); // intersection has at least 2 neighbours
                for (auto neighbour : node->neighbours) {
                    assert(neighbour->neighbours.size() <= 2);  // an intersection musn't have an intersection as neighbour

                    // Link our neighbours directly to each other
                    for (auto n : node->neighbours) {
                        if (n != neighbour) {
                            neighbour->neighbours.push_back(n);
                        }
                    }

                    // Update their location to be when pacman's bounds hit the intersection tile
                    FPoint direction = node->location - neighbour->location;
                    direction.normalise();
                    neighbour->location += direction * (TILE_SIZE - PLAYER_SIZE)/2.0;

                    // remove us
                    auto& vec = neighbour->neighbours;
                    vec.erase(std::find(vec.begin(), vec.end(), node));  // damn the complexity of simply removing a node
                }

                delete node;
                node = NULL;
            }
        }
    }

    // create pacman spawn
    spawn = new Node(FPoint(14, 23.5) * TILE_SIZE);
    spawn->neighbours.push_back(nodes.at(at(14, 23))); // Note: symmetrical map, just going to the right is fine

    ensure_valid(nodes, nodes);
    ensure_valid(spawn, nodes);

    // print stats
    cout << "Pacman branching factor: " << get_branching_factor(nodes) << endl;
}

PacmanNodes::~PacmanNodes() {
    delete spawn;
}

    }
}
