/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Nodes.h"
#include "Node.h"
#include "../Utility.h"
#include "../Constants.h"
#include "../specification/Walls.h"
#include "../util/assertion.h"
#include "../util/serialization.h"

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

static_assert(PLAYER_SIZE < 2.0 * TILE_SIZE, "Node map requires this");

using std::vector;
using std::endl;

using ::PACMAN::SPECIFICATION::walls;

namespace PACMAN {
    namespace MODEL {

Nodes::Nodes()
:   nodes(MAP_WIDTH * MAP_HEIGHT)
{
    // create a node for each free tile
    for (int x=0; x < MAP_WIDTH; ++x) {
        for (int y=0; y < MAP_HEIGHT; ++y) {
            int center = at(x, y);
            if (walls[center] == 0) {
                // skip ghost pen tiles
                if (x >= 11 && x <= 16 && y >= 13 && y <= 15) {
                    continue;
                }

                // skip unreachable empty tiles
                if (x >= 0 && x <= 4 && y >= 10 && y <= 12) { // tunnel surroundings
                    continue;
                }
                if (x >= 0 && x <= 4 && y >= 16 && y <= 18) {
                    continue;
                }
                if (x >= MAP_WIDTH-5 && x <= MAP_WIDTH-1 && y >= 10 && y <= 12) {
                    continue;
                }
                if (x >= MAP_WIDTH-5 && x <= MAP_WIDTH-1 && y >= 16 && y <= 18) {
                    continue;
                }

                if (y == 3 && (x == 3 || x == 4 || (x >= 8 && x <= 10) || (x >= 17 && x <= 19) || x == 23 || x == 24)) { // a few tiles at top
                    continue;
                }

                // add this one
                nodes.at(center) = new Node(FPoint(x+0.5, y+0.5) * TILE_SIZE);
            }
        }
    }

    // add NESW neighbours
    for (int x=0; x < MAP_WIDTH; ++x) {
        for (int y=0; y < MAP_HEIGHT; ++y) {
            auto node = nodes.at(at(x, y));
            if (!node)
                continue;

            int north = at(x, y-1);
            if (nodes.at(north)) {
                node->neighbours.push_back(nodes.at(north));
            }

            int south = at(x, y+1);
            if (nodes.at(south)) {
                node->neighbours.push_back(nodes.at(south));
            }

            int east = at_wrap(x+1, y); // TODO the wrapping code can be centralised (and you could do it with shorter with x%MAP_WIDTH), at_wrapped or at(wrap(p)) or tunnel_wrap
            if (nodes.at(east)) {
                node->neighbours.push_back(nodes.at(east));
            }

            int west = at_wrap(x-1, y);
            if (nodes.at(west)) {
                node->neighbours.push_back(nodes.at(west));
            }
        }
    }

    ensure_valid(nodes, nodes);
}

Nodes::~Nodes()
{
    for (auto node : nodes) {
        if (node) {
            delete node;
        }
    }
}

void Nodes::ensure_valid(const vector<Node*>& nodes, const vector<Node*>& all_nodes) const {
    for (auto node : nodes) {
        if (node)
            ensure_valid(node, all_nodes);
    }
    ENSURE(nodes.size() > 0);
}

// check node
void Nodes::ensure_valid(const Node* node, const vector<Node*>& all_nodes) const {
    // within map bounds
    ENSURE(node->location.x > 0.0);
    ENSURE(node->location.y > 0.0);
    ENSURE(node->location.x < MAP_WIDTH * TILE_SIZE);
    ENSURE(node->location.y < MAP_HEIGHT * TILE_SIZE);

    // required by PlayerState
    ENSURE(node->neighbours.size() <= MAX_ACTION_COUNT);

    // must have neighbours
    ENSURE(node->neighbours.size() > 0);
    for (auto neighbour : node->neighbours) {
        ENSURE(std::find(all_nodes.begin(), all_nodes.end(), neighbour) != all_nodes.end());
        ENSURE(neighbour->location != node->location);
    }
}

void Nodes::draw(shared_ptr<SDL_Surface> screen) const {
    for (auto node : nodes) {
        if (!node)
            continue;

        for (auto neighbour : node->neighbours) {
            int retval = lineColor(screen.get(), (int)node->location.x, (int)node->location.y, (int)neighbour->location.x, (int)neighbour->location.y, 0xFF000077);// Uint32
            ASSERT(retval == 0);
        }
    }

    SDL_Rect r;
    r.w = r.h = 3;
    for (auto node : nodes) {
        if (!node)
            continue;

        r.x = (int)node->location.x;
        r.y = (int)node->location.y;
        SDL_FillRect(screen.get(), &r, 0x00FF00);
    }
}

double Nodes::get_branching_factor(const vector<Node*>& nodes) const {
    double branching_factor = 0.0;
    int count = 0;
    for (auto node : nodes) {
        if (node) {
            branching_factor += node->neighbours.size();
            count++;
        }
    }
    branching_factor /= count;
    return branching_factor;
}

const Node* Nodes::load(std::istream& in, const std::vector<Node*>& nodes) const {
    std::iterator_traits<vector<Node*>::iterator>::difference_type index;
    read(in, index);
    return nodes.at(index);
}

void Nodes::save(std::ostream& out, const Node* node, const std::vector<Node*>& nodes) const {
    auto it = std::find(nodes.begin(), nodes.end(), node);
    REQUIRE(it != nodes.end());
    ASSERT(std::distance(nodes.begin(), nodes.begin()) == 0); // TODO rm this line after a succesful run
    write(out, std::distance(nodes.begin(), it));
}

}}
