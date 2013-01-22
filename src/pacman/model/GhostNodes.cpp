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
#include "../Utility.h"
#include "../Constants.h"
#include "../specification/Walls.h"
#include "../util/serialization.h"

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

using std::vector;
using std::cout;
using std::endl;
using std::make_pair;

namespace PACMAN {
    namespace MODEL {

const GhostNodes GHOST_NODES;

GhostNodes::GhostNodes() 
:   spawns(GHOST_COUNT),
    respawns(GHOST_COUNT)
{
    eliminate_redundant_nodes();

    // ghost pen nodes
    spawns.at(GHOST_BLINKY) = new Node(FPoint(14, 11.5) * TILE_SIZE);
    spawns.at(GHOST_PINKY) = new Node(FPoint(14, 14) * TILE_SIZE);
    spawns.at(GHOST_INKY) = new Node(FPoint(12, 14) * TILE_SIZE);
    spawns.at(GHOST_CLYDE) = new Node(FPoint(16, 14) * TILE_SIZE);

    spawns.at(GHOST_INKY)->neighbours.push_back(spawns.at(GHOST_PINKY));
    spawns.at(GHOST_CLYDE)->neighbours.push_back(spawns.at(GHOST_PINKY));
    spawns.at(GHOST_PINKY)->neighbours.push_back(spawns.at(GHOST_BLINKY));
    spawns.at(GHOST_BLINKY)->neighbours.push_back(nodes.at(at(12, 11)));
    spawns.at(GHOST_BLINKY)->neighbours.push_back(nodes.at(at(15, 11)));

    ensure_valid(nodes, nodes);
    vector<Node*> all_nodes;
    all_nodes.reserve(nodes.size() + spawns.size());
    all_nodes.insert(all_nodes.end(), nodes.begin(), nodes.end());
    all_nodes.insert(all_nodes.end(), spawns.begin(), spawns.end());
    ensure_valid(spawns, all_nodes);

    respawns.at(GHOST_BLINKY) = spawns.at(GHOST_PINKY);
    respawns.at(GHOST_PINKY) = spawns.at(GHOST_PINKY);
    respawns.at(GHOST_INKY) = spawns.at(GHOST_INKY);
    respawns.at(GHOST_CLYDE) = spawns.at(GHOST_CLYDE);

    add_respawn_paths();

    // print stats
    cout << "Ghost branching factor: " << get_branching_factor(nodes) << endl;
}

void GhostNodes::add_respawn_paths() {
    // Overall structure: like an A* search with distance as cost, PINKY spawn as origin, and no destination/goal

    std::multimap<double, const Node*> fringe;

    fringe.insert(make_pair(0.0, spawns.at(GHOST_PINKY)));

    while (!fringe.empty()) {
        auto it = fringe.begin();
        const double cost = (*it).first;
        const Node* node = (*it).second;
        fringe.erase(it);

        if (cost > get_cost(node)) {
            continue;  // node's closed; we already expanded it
        }

        for (const auto neighbour : node->get_neighbours()) {
            double neighbour_cost = cost + (neighbour->get_location() - node->get_location()).length();

            if (neighbour_cost < get_cost(neighbour)) {
                // found a better path to this neighbour
                min_costs[neighbour] = neighbour_cost;
                towards_spawn[neighbour] = node;
                fringe.insert(make_pair(neighbour_cost, neighbour));
            }
        }
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

        auto o = origin->location;
        auto d = destination->location;
        retval = lineColor(screen.get(), (int)o.x, (int)o.y, (int)d.x, (int)d.y, 0x00FF00FF);
        ASSERT(retval == 0);

        // offset along origin-destination
        auto offset = o - d;
        offset.normalise();
        offset.x *= 12;
        offset.y *= 12;

        // offset perpendicular to o-d
        FPoint perpendicular_offset(offset.y / 2.0, offset.x / 2.0);

        auto p1 = d + offset + perpendicular_offset;
        auto p2 = d + offset - perpendicular_offset;
        retval = filledTrigonColor(screen.get(), (int)d.x, (int)d.y, (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, 0xFF0000FF);
        ASSERT(retval == 0);
    }
}

double GhostNodes::get_cost(const Node* node) const {
    REQUIRE(node);
    auto current_min_cost = min_costs.find(node);
    if (current_min_cost == min_costs.end()) {
        return std::numeric_limits<double>::infinity();
    }
    else {
        return (*current_min_cost).second;
    }
}

const Node* GhostNodes::get_node_towards_spawn(const Node* origin) const {
    ASSERT(origin);
    return towards_spawn.at(origin);
}

const std::vector<Node*> GhostNodes::get_respawns() const {
    return respawns;
}

const std::vector<Node*> GhostNodes::get_spawns() const {
    return spawns;
}

}}
