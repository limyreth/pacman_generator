/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "PacmanState.h"
#include "PacmanNodes.h"
#include "../util/util.h"
#include "../specification/Walls.h"

using ::PACMAN::SPECIFICATION::walls;

namespace PACMAN {
    namespace MODEL {

PacmanState::PacmanState()
{
}

PacmanState::PacmanState(const int origin_id, const int destination_id, FPoint pos)
:   PlayerState(PACMAN_NODES.get(origin_id), PACMAN_NODES.get(destination_id), pos)
    
{
}

PacmanState::PacmanState(const Node& initial_node)
:   PlayerState(initial_node)
{
}

bool PacmanState::operator==(const PacmanState& o) const {
    return PlayerState::operator==(o);
}

IPoint PacmanState::get_tile_pos() const {
    IPoint tile_pos = PlayerState::get_tile_pos();

    // special case: see cornering
    if (walls[at(tile_pos)]) {
        // find the closest intersection tile:
        // find which quadrant of the wall tile we're in. Upper left = (0, 0), lower right quadrant = (1, 1)
         int x = (get_pos().x - tile_pos.x * TILE_SIZE) / (TILE_SIZE / 2.0);
         int y = (get_pos().y - tile_pos.y * TILE_SIZE) / (TILE_SIZE / 2.0);

         tile_pos.x += x == 0 ? -1 : 1;
         tile_pos.y += y == 0 ? -1 : 1;
         ASSERT(!walls[at(tile_pos)]);
    }

    return tile_pos;
}

const Nodes& PacmanState::get_nodes() const {
    return PACMAN_NODES;
}

}}
