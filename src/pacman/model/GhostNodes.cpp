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

using std::vector;
using std::cout;
using std::endl;

namespace PACMAN {
    namespace MODEL {

const GhostNodes GHOST_NODES;

GhostNodes::GhostNodes() 
:   spawns(GHOST_COUNT)
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

    // print stats
    cout << "Ghost branching factor: " << get_branching_factor(nodes) << endl;
}

GhostNodes::~GhostNodes()
{
    for (auto node : spawns) {
        delete node;
    }
}

const Node* GhostNodes::load(std::istream& in) const {
    char choice;
    read(in, choice);
    if (choice == (char)0) {
        return NULL;
    }
    else if (choice == (char)1) {
        return Nodes::load(in, spawns);
    }
    else {
        ASSERT(choice == (char)2);
        return Nodes::load(in, nodes);
    }
}

void GhostNodes::save(std::ostream& out, const Node* node) const {
    if (node == NULL) {
        write(out, (char)0);
    }
    else if (std::find(spawns.begin(), spawns.end(), node) != spawns.end()) {
        write(out, (char)1);
        Nodes::save(out, node, spawns);
    }
    else {
        write(out, (char)2);
        Nodes::save(out, node, nodes);
    }
}

void GhostNodes::draw(shared_ptr<SDL_Surface> buffer) const {
    Nodes::draw(buffer, nodes, 0xFF0000, 0xFF000077);
    Nodes::draw(buffer, spawns, 0x0000FF, 0x0000FFFF);
}

}}
