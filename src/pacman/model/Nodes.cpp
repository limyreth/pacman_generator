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
#include "../Constants.h"
#include "../specification/Walls.h"
#include "../util/assertion.h"
#include "../util/util.h"

#include <algorithm>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

using std::vector;
using std::endl;
using std::shared_ptr;
using std::string;

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
            if (!walls[center]) {
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

            int east = at_wrap(x+1, y);
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

void Nodes::draw(shared_ptr<SDL_Surface> screen, const std::vector<Node*>& nodes, uint32_t node_color, uint32_t edge_color) const {
    for (auto node : nodes) {
        if (!node)
            continue;

        draw(screen, *node, node_color, edge_color);
    }
}

void Nodes::draw(shared_ptr<SDL_Surface> screen, const Node& node, uint32_t node_color, uint32_t edge_color) const {
    for (auto neighbour : node.neighbours) {
        int retval = lineColor(screen.get(), (int)node.location.x, (int)node.location.y, (int)neighbour->location.x, (int)neighbour->location.y, edge_color);
        ASSERT(retval == 0);
    }

    draw(screen, node, node_color);
}

void Nodes::draw(shared_ptr<SDL_Surface> screen, const Node& node, uint32_t node_color) const {
    SDL_Rect r;
    r.w = r.h = 5;
    r.x = (int)node.location.x - 2;
    r.y = (int)node.location.y - 2;
    SDL_FillRect(screen.get(), &r, node_color);
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

/*
 * Merges nodes where the player has no real choice when reversal is not allowed
 *
 * Note: this limits the ability of players to reverse. So don't use this if
 * you do want to allow them to reverse (often).
 */
void Nodes::eliminate_redundant_nodes() {
    // merge by column
    for (int x=0; x < MAP_WIDTH; ++x) {
        Node* head = NULL; // head of the mergeable train of nodes
        Node* mid = NULL; // either a mid part of the train, but turn out to be a tail
        for (int y=0; y < MAP_HEIGHT; ++y) {
            auto node = nodes[at(x, y)];

            if (!node) {
                head = NULL;
                mid = NULL;  // mid was actually a tail
            }
            else if (head == NULL || node->neighbours.size() > 2) {
                head = node;
                if (mid) {
                    // new head is also the tail of the previous train
                    eliminate(x, y-1);
                    mid = NULL;
                }
            }
            else if (head) {
                if (mid) {
                    eliminate(x, y-1);
                }
                mid = node;
            }
        }
    }

    // merge by row (copy past ftw)
    for (int y=0; y < MAP_HEIGHT; ++y) {
        Node* head = NULL; // head of the mergeable train of nodes
        Node* mid = NULL; // either a mid part of the train, but turn out to be a tail
        for (int x=0; x < MAP_WIDTH; ++x) {
            auto node = nodes[at(x, y)];

            if (!node) {
                head = NULL;
                mid = NULL;  // mid was actually a tail
            }
            else if (head == NULL || node->neighbours.size() > 2) {
                head = node;
                if (mid) {
                    // new head is also the tail of the previous train
                    eliminate(x-1, y);
                    mid = NULL;
                }
            }
            else if (head) {
                if (mid) {
                    eliminate(x-1, y);
                }
                mid = node;
            }
        }
    }

    // eliminate the 2 ends of the tunnel (as they wrap)
    eliminate(0, 14);
    eliminate(MAP_WIDTH-1, 14);
    
    ensure_valid(nodes, nodes);
}

void Nodes::eliminate(int x, int y) {
    auto node = nodes.at(at(x, y));
    REQUIRE(node);
    for (auto neighbour : node->neighbours) {
        // Link neighbours to each other
        for (auto n : node->neighbours) {
            if (n != neighbour) {
                neighbour->neighbours.push_back(n);
            }
        }

        // remove node from neigbour's list
        auto& vec = neighbour->neighbours;
        vec.erase(std::find(vec.begin(), vec.end(), node));
    }

    // remove node
    nodes.at(at(x, y)) = NULL;
    delete node;
}

/*
 * Whether travelling between a and b requires wrapping the screen
 */
bool Nodes::are_connected_through_wrapping(const Node& a, const Node& b) const {
    // requires of internal contract with derived class
    REQUIRE(left_tunnel_node);
    REQUIRE(right_tunnel_node);
    return (&a == left_tunnel_node && &b == right_tunnel_node) || (&a == right_tunnel_node && &b == left_tunnel_node);
}

int Nodes::get_id(const Node& node, const std::vector<Node*>& nodes) const {
    auto it = std::find(nodes.begin(), nodes.end(), &node);
    if (it == nodes.end()) {
        return -1;
    }
    else {
        return std::distance(nodes.begin(), it);
    }
}

bool Nodes::has_node_equivalent_to(int id, FPoint location, const vector<int>& neighbour_ids) const {
    auto node = get(id);

    if (node->get_location() != location) {
        return false;
    }


    if (node->get_neighbours().size() != neighbour_ids.size()) {
        return false;
    }

    for (auto neighbour_id : neighbour_ids) {
        auto neighbour = get(neighbour_id);
        auto& neighbours = node->get_neighbours();
        if (std::find(neighbours.begin(), neighbours.end(), neighbour) == neighbours.end()) {
            return false;
        }
    }

    return true;
}

void Nodes::print_nodes(std::ostream& out, const vector<Node*>& nodes, string name) const {
    for (auto node : nodes) {
        if (node == NULL) {
            continue;
        }

        print_node(out, *node, name);
    }
}

void Nodes::print_node(std::ostream& out, Node& node, string name) const {
    auto old_precision = out.precision();
    out.precision(20);

    out << "{" << endl;
    out << "vector<int> neighbour_ids;" << endl;
    for (auto neighbour : node.get_neighbours()) {
        out << "neighbour_ids.push_back(" << get_id(neighbour) << ");" << endl;
    }
    out << "ASSERT(" << name << ".has_node_equivalent_to(" << get_id(&node) << ", FPoint" << node.get_location() << ", neighbour_ids));" << endl;
    out << "}" << endl;
    out << endl;

    out.precision(old_precision);
}

}}
