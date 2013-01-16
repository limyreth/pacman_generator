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
#include "../util/serialization.h"

using std::vector;
using std::cout;
using std::endl;

using ::PACMAN::SPECIFICATION::walls;

namespace PACMAN {
    namespace MODEL {

const PacmanNodes PACMAN_NODES;

PacmanNodes::PacmanNodes() {
    for (int x=0; x < MAP_WIDTH; ++x) {
        for (int y=0; y < MAP_HEIGHT; ++y) {
            auto& node = nodes.at(at(x, y));
            if (!node)
                continue; 
            // if we are intersection/corner
            if ((walls[at_wrap(x-1,y)] || !walls[at_wrap(x+1,y)])  // a free tile along x-axis
                    && (!walls[at(x, y-1)] || walls[at(x, y+1)])== false )  // and a free tile along the y-axis
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

const Node* PacmanNodes::load(std::istream& in) const {
    char choice;
    read(in, choice);
    if (choice == (char)0) {
        return NULL;
    }
    else if (choice == (char)1) {
        return spawn;
    }
    else {
        ASSERT(choice == (char)2);
        return Nodes::load(in, nodes);
    }
}

void PacmanNodes::save(std::ostream& out, const Node* node) const {
    if (node == NULL) {
        write(out, (char)0);
    }
    else if (node == spawn) {
        write(out, (char)1);
    }
    else {
        write(out, (char)2);
        Nodes::save(out, node, nodes);
    }
}

}}
