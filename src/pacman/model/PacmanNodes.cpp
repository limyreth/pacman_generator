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
#include "../Constants.h"
#include "../specification/Walls.h"
#include "../util/util.h"

#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::shared_ptr;

using ::PACMAN::SPECIFICATION::walls;

namespace PACMAN {
    namespace MODEL {

const PacmanNodes PACMAN_NODES;

PacmanNodes::PacmanNodes() {
    left_tunnel_node = nodes.at(at(5, 14));
    right_tunnel_node = nodes.at(at(MAP_WIDTH-6, 14));

    for (int x=0; x < MAP_WIDTH; ++x) {
        for (int y=0; y < MAP_HEIGHT; ++y) {
            auto& node = nodes.at(at(x, y));
            if (!node)
                continue; 
            // if we are intersection/corner
            if ((!walls[at_wrap(x-1,y)] || !walls[at_wrap(x+1,y)])  // a free tile along x-axis
                    && (!walls[at(x, y-1)] || !walls[at(x, y+1)]))  // and a free tile along the y-axis
            {
                ASSERT(node->neighbours.size() >= 2); // intersection has at least 2 neighbours
                for (auto neighbour : node->neighbours) {
                    // Update neighbour location to be when pacman's bounds hit the intersection tile
                    FPoint direction = node->location - neighbour->location;
                    direction.normalise();
                    neighbour->location += direction * (TILE_SIZE - PLAYER_SIZE)/2.0;
                }

                eliminate(x, y);
            }
        }
    }

    eliminate_redundant_nodes();

    // create pacman spawn
    spawn = new Node(FPoint(14, 23.5) * TILE_SIZE);
    spawn->neighbours.push_back(nodes.at(at(14, 23))); // Note: symmetrical map, just going to the right is fine

    ensure_valid(nodes, nodes);
    ensure_valid(spawn, nodes);

    ENSURE(left_tunnel_node);
    ENSURE(right_tunnel_node);
    ENSURE(std::find(nodes.begin(), nodes.end(), left_tunnel_node) != nodes.end());
    ENSURE(std::find(nodes.begin(), nodes.end(), right_tunnel_node) != nodes.end());

    // print stats
    cout << "Pacman branching factor: " << get_branching_factor(nodes) << endl;
}

PacmanNodes::~PacmanNodes() {
    delete spawn;
}

void PacmanNodes::draw(shared_ptr<SDL_Surface> buffer) const {
    Nodes::draw(buffer, nodes, 0xFF0000, 0xFF000077);
    Nodes::draw(buffer, *spawn, 0x00FF00, 0x00FF00FF);
}

const Node& PacmanNodes::get_spawn() const {
    return *spawn;
}

const Node* PacmanNodes::get(int id) const {
    if (id >= 0) {
        return nodes.at(id);
    }
    else if (id == -1) {
        return spawn;
    }
    else {
        ASSERT(id == -2);
        return NULL;
    }
}

int PacmanNodes::get_id(const Node* node) const {
    if (node == NULL) {
        return -2;
    }
    return Nodes::get_id(*node, nodes);
}

}}
