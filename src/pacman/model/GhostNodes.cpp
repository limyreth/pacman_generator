/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "GhostNodes.h"
#include "Node.h"
#include "../Constants.h"
#include "../specification/Walls.h"
#include "../util/util.h"

#include <algorithm>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

using std::vector;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::make_pair;

namespace PACMAN {
    namespace MODEL {

const GhostNodes GHOST_NODES;

GhostNodes::GhostNodes() 
:   respawns(GHOST_COUNT),
    spawns(GHOST_COUNT)
{
    left_tunnel_node = nodes.at(at(6, 14));
    right_tunnel_node = nodes.at(at(MAP_WIDTH-7, 14));

    eliminate_redundant_nodes();

    // ghost pen nodes
    spawns.at(GHOST_BLINKY) = new Node(FPoint(14, 11.5));
    spawns.at(GHOST_PINKY) = new Node(FPoint(14, 14));
    spawns.at(GHOST_INKY) = new Node(FPoint(12, 14));
    spawns.at(GHOST_CLYDE) = new Node(FPoint(16, 14));

    spawns.at(GHOST_INKY)->neighbours.push_back(spawns.at(GHOST_PINKY));
    spawns.at(GHOST_CLYDE)->neighbours.push_back(spawns.at(GHOST_PINKY));
    spawns.at(GHOST_PINKY)->neighbours.push_back(spawns.at(GHOST_BLINKY));
    spawns.at(GHOST_BLINKY)->neighbours.push_back(nodes.at(at(12, 11)));
    spawns.at(GHOST_BLINKY)->neighbours.push_back(nodes.at(at(15, 11)));

    // respawns
    respawns.at(GHOST_BLINKY) = spawns.at(GHOST_PINKY);
    respawns.at(GHOST_PINKY) = spawns.at(GHOST_PINKY);
    respawns.at(GHOST_INKY) = spawns.at(GHOST_INKY);
    respawns.at(GHOST_CLYDE) = spawns.at(GHOST_CLYDE);

    add_respawn_paths();

    // print stats
    cout << "Ghost branching factor: " << get_branching_factor(nodes) << endl;

    // ensures
    ensure_valid(nodes, nodes);

    vector<Node*> all_nodes;
    all_nodes.reserve(nodes.size() + spawns.size());
    all_nodes.insert(all_nodes.end(), nodes.begin(), nodes.end());
    all_nodes.insert(all_nodes.end(), spawns.begin(), spawns.end());
    ensure_valid(spawns, all_nodes);
    ENSURE(spawns.size() == PLAYER_COUNT-1);

    ENSURE(respawns.size() == PLAYER_COUNT-1);
    for (auto respawn : respawns) {  // respawns is subset of spawns
        std::find(spawns.begin(), spawns.end(), respawn) != spawns.end();
    }

    ENSURE(left_tunnel_node);
    ENSURE(right_tunnel_node);
    ENSURE(std::find(nodes.begin(), nodes.end(), left_tunnel_node) != nodes.end());
    ENSURE(std::find(nodes.begin(), nodes.end(), right_tunnel_node) != nodes.end());
}

void GhostNodes::add_respawn_paths() {
    // Overall structure: like an A* search with distance as cost, PINKY spawn as origin, and no destination/goal
    ensure_valid(nodes, nodes);  // =REQUIRE

    std::multimap<float, const Node*> fringe;

    fringe.insert(make_pair(0.0f, spawns.at(GHOST_PINKY)));

    while (!fringe.empty()) {
        auto it = fringe.begin();
        const float cost = (*it).first;
        const Node* node = (*it).second;
        fringe.erase(it);

        if (cost > get_cost(*node)) {
            continue;  // node's closed; we already expanded it
        }

        for (const auto neighbour : node->get_neighbours()) {
            float neighbour_cost = cost + (neighbour->get_location() - node->get_location()).length();

            if (neighbour_cost < get_cost(*neighbour)) {
                // found a better path to this neighbour
                min_costs[neighbour] = neighbour_cost;
                towards_spawn[neighbour] = node;
                fringe.insert(make_pair(neighbour_cost, neighbour));
            }
        }
    }

    auto more_nodes = nodes;
    //more_nodes.push_back(spawns.at(GHOST_BLINKY));
    for (auto node : more_nodes) {
        if (!node) continue;

        ENSURE(min_costs.find(node) != min_costs.end());
        ENSURE(min_costs.find(node)->second != std::numeric_limits<float>::infinity());
        ENSURE(min_costs.find(node)->second >= 0.0f);

        ENSURE(towards_spawn.find(node) != towards_spawn.end());
        ENSURE(towards_spawn.find(node)->second != NULL);
    }
}

GhostNodes::~GhostNodes()
{
    for (auto node : spawns) {
        delete node;
    }
}

void GhostNodes::draw(shared_ptr<SDL_Surface> buffer) const {
    Nodes::draw(buffer, nodes, 0xFF0000, 0xFF000077);
    Nodes::draw(buffer, spawns, 0x00FF00, 0x00FF00FF);
}

void GhostNodes::draw_respawn_paths(shared_ptr<SDL_Surface> screen) const {
    for (auto it = towards_spawn.begin(); it != towards_spawn.end(); it++) {
        auto origin = it->first;
        auto destination = it->second;

        // draw arrow from origin to destination
        int retval;

        auto o = origin->location * ::PACMAN::GUI::TILE_SIZE;
        auto d = destination->location * ::PACMAN::GUI::TILE_SIZE;
        retval = lineColor(screen.get(), (int)o.x, (int)o.y, (int)d.x, (int)d.y, 0x00FF00FF);
        ASSERT(retval == 0);

        // offset along origin-destination
        auto offset = o - d;
        offset.normalise();
        offset.x *= 12.0f;
        offset.y *= 12.0f;

        // offset perpendicular to o-d
        FPoint perpendicular_offset(offset.y / 2.0f, offset.x / 2.0f);

        auto p1 = d + offset + perpendicular_offset;
        auto p2 = d + offset - perpendicular_offset;
        retval = filledTrigonColor(screen.get(), (int)d.x, (int)d.y, (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, 0xFF0000FF);
        ASSERT(retval == 0);
    }
}

float GhostNodes::get_cost(const Node& node) const {
    //REQUIRE(node in nodes.union(blinky spawn))
    //ENSURE(retval != infinity after ctor)
    auto current_min_cost = min_costs.find(&node);
    if (current_min_cost == min_costs.end()) {
        return std::numeric_limits<float>::infinity();
    }
    else {
        return (*current_min_cost).second;
    }
}

const Node& GhostNodes::get_node_towards_spawn(const Node& origin) const {
    //REQUIRE(node in nodes.union(blinky spawn))
    //ENSURE(retval != NULL && is of this Nodes)
    return *towards_spawn.at(&origin);
}

const std::vector<Node*> GhostNodes::get_respawns() const {
    //ENSURE(respawns.size() == PLAYER_COUNT-1)
    return respawns;
}

const std::vector<Node*> GhostNodes::get_spawns() const {
    //ENSURE(spawns.size() == PLAYER_COUNT-1)
    return spawns;
}

const Node* GhostNodes::get(int id) const {
    if (id == -1) {
        return NULL;
    }
    ASSERT(id >= 0);

    int index = id >> 1;
    if ((id & 1) == 0) {
        return nodes.at(index);
    }
    else {
        return spawns.at(index);
    }
}

int GhostNodes::get_id(const Node* node) const {
    if (node == NULL) {
        return -1;
    }

    auto id = Nodes::get_id(*node, nodes);
    if (id >= 0) {
        id = (id << 1) + 0;
    }
    else {
        id = Nodes::get_id(*node, spawns);
        id = (id << 1) + 1;
    }
    return id;
}

bool GhostNodes::is_spawn_node(const Node* node) const {
    return std::find(spawns.begin(), spawns.end(), node) != spawns.end();
}

void GhostNodes::print_code(std::ostream& out) const {
    print_nodes(out, nodes, "GHOST_NODES");
    print_nodes(out, spawns, "GHOST_NODES");
}

}}
