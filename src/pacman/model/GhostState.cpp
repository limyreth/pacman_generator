/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "GhostState.h"
#include "GhostNodes.h"
#include "Node.h"
#include "../Utility.h"
#include "../util/serialization.h"

// TODO dead ghost takes shortest path back to correct pen tile

// TODO size enums to 1 byte

using std::endl;

namespace PACMAN {
    namespace MODEL {

GhostState::GhostState()
{
}

GhostState::GhostState(const Node* initial_node)
:   PlayerState(initial_node), state(NORMAL)
{
}

// player_index: current player
double GhostState::move(double distance) {
    double movement_excess = PlayerState::move(distance);

    if (state != DEAD) {
        return movement_excess;
    }
    else {
        // path finding for dead ghosts:

        if (movement_excess >= 0.0) {
            auto respawn_node = GHOST_NODES.get_spawns().at(GHOST_PINKY);
            if (destination == respawn_node) {
                // respawn node reached, respawn!
                state = NORMAL;
                origin = NULL;
                return movement_excess;
            } else {
                origin = destination;
                destination = GHOST_NODES.get_node_towards_spawn(destination);
                return move(movement_excess);
            }
        }
    }
}

void GhostState::die() {
    state = GhostState::DEAD;

    // initial path finding to respawn point: which way is shortest, through origin or destination?
    ASSERT(origin);
    double origin_cost = (get_pos() - origin->get_location()).length() + GHOST_NODES.get_cost(origin);
    double destination_cost = (get_pos() - destination->get_location()).length() + GHOST_NODES.get_cost(destination);
    if (origin_cost < destination_cost) {
        std::swap(destination, origin);
    }
}

bool GhostState::is_in_tunnel() {
    return false; // TODO implement this damn it
}

bool GhostState::operator==(const GhostState& o) const {
    return PlayerState::operator==(o) &&
        o.state == state;
}

// Note: this has little meaning other than that when it changes, a new action may be chosen (which is by crossing any grid line with offset half a tile)

}}
