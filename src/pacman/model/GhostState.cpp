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
#include "../util/util.h"

#include <boost/scope_exit.hpp>

using std::cout;
using std::endl;
using std::string;

namespace PACMAN {
    namespace MODEL {

GhostState::GhostState()
{
}

GhostState::GhostState(const int origin_id, const int destination_id, FPoint pos, State state)
:   PlayerState(GHOST_NODES.get(origin_id), GHOST_NODES.get(destination_id), pos),
    state(state)
{
}

GhostState::GhostState(const Node& initial_node)
:   PlayerState(initial_node), 
    state(WAITING)
{
}

// player_index: current player
double GhostState::move(double distance, int player_index) {
    if (state == WAITING) {
        return -1.0;
    }

    double movement_excess = PlayerState::move(distance, player_index);
    double retval;

    BOOST_SCOPE_EXIT(&retval, &state) {
        ENSURE(state != DEAD || retval < 0.0);
    } BOOST_SCOPE_EXIT_END

    if (state != DEAD || movement_excess < 0.0) {
        return retval = movement_excess;
    }
    else {
        // path finding for dead ghosts:

        // destination reached, need to pick next destination
        auto respawn_node = GHOST_NODES.get_respawns().at(player_index - 1);
        if (destination == respawn_node) {
            // respawn node reached, respawn!
            state = NORMAL;
            origin = NULL;
            return retval = movement_excess;
        } else {
            origin = destination;
            if (destination == GHOST_NODES.get_respawns().at(GHOST_PINKY)) {
                // we couldn't fit the last pointer towards respawn point
                // for CLYDE and INKY, because the path splits at PINKY;
                // so we hardcode the last step this way
                destination = respawn_node;
            }
            else {
                destination = &GHOST_NODES.get_node_towards_spawn(*destination);
            }
            return retval = move(movement_excess, player_index);
        }
    }
}

void GhostState::act(Action action) {
    REQUIRE(state != DEAD);  // dead ghosts have no free will, they must return to the ghost pen
    PlayerState::act(action);
}

void GhostState::die() {
    state = DEAD;

    // initial path finding to respawn point: which way is shortest, through origin or destination?
    ASSERT(origin);
    double origin_cost = (get_pos() - origin->get_location()).length() + GHOST_NODES.get_cost(*origin);
    double destination_cost = (get_pos() - destination->get_location()).length() + GHOST_NODES.get_cost(*destination);
    if (origin_cost < destination_cost) {
        std::swap(origin, destination);
    }
}

bool GhostState::is_in_tunnel() {
    auto tpos = get_tile_pos();
    return tpos.y == 14 && ((tpos.x >= 0 && tpos.x <= 5) || (tpos.x >= MAP_WIDTH - 6 && tpos.x <= MAP_WIDTH - 1));
}

bool GhostState::operator==(const GhostState& o) const {
    return PlayerState::operator==(o) &&
        o.state == state;
}

const Nodes& GhostState::get_nodes() const {
    return GHOST_NODES;
}

bool GhostState::is_leaving_pen() const {
    GHOST_NODES.is_spawn_node(origin);
}

bool GhostState::can_reverse() const {
    return state != DEAD && state != WAITING && 
        !is_leaving_pen() &&
        PlayerState::can_reverse();
}

void GhostState::leave_pen() {
    REQUIRE(state == WAITING);
    state = NORMAL;
}

void GhostState::print(std::ostream& out, string prefix, string name) const {
    PlayerState::print(out, prefix, name);
    out << prefix << "const GhostState::State " << name << "_state = (GhostState::State)" << state << ";" << endl;
}

// Note: this has little meaning other than that when it changes, a new action may be chosen (which is by crossing any grid line with offset half a tile)

}}
