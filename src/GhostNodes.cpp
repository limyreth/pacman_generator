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
#include "Utility.h"
#include "Constants.h"
#include "Walls.h"

using std::vector;
using std::cout;
using std::endl;

const vector<Node*> GhostNodes::init() {
    Nodes::init();

    // ghost pen nodes
    vector<Node*> spawns(GHOST_COUNT);
    
    spawns.at(GHOST_BLINKY) = new Node(FPoint(14, 11.5) * TILE_SIZE);
    spawns.at(GHOST_PINKY) = new Node(FPoint(14, 14) * TILE_SIZE);
    spawns.at(GHOST_INKY) = new Node(FPoint(12, 14) * TILE_SIZE);
    spawns.at(GHOST_CLYDE) = new Node(FPoint(16, 14) * TILE_SIZE);

    spawns.at(GHOST_INKY)->neighbours.push_back(spawns.at(GHOST_PINKY));
    spawns.at(GHOST_CLYDE)->neighbours.push_back(spawns.at(GHOST_PINKY));
    spawns.at(GHOST_PINKY)->neighbours.push_back(spawns.at(GHOST_BLINKY));
    spawns.at(GHOST_BLINKY)->neighbours.push_back(nodes.at(at(13, 11)));
    spawns.at(GHOST_BLINKY)->neighbours.push_back(nodes.at(at(14, 11)));

    assert_valid(nodes);
    assert_valid(spawns);

    // print stats
    cout << "Ghost branching factor: " << get_branching_factor(nodes) << endl;

    return spawns;
}

