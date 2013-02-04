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
using namespace ::PACMAN::SPECIFICATION;

namespace PACMAN {
    namespace MODEL {

GhostState::GhostState()
{
}

GhostState::GhostState(const int origin_id, const int destination_id, FPoint pos, State state, bool vulnerable)
:   PlayerState(GHOST_NODES.get(origin_id), GHOST_NODES.get(destination_id), pos),
    state(state),
    vulnerable(vulnerable)
{
}

GhostState::GhostState(const Node& initial_node)
:   PlayerState(initial_node), 
    state(WAITING),
    vulnerable(false)
{
}

// player_index: current player
float GhostState::move(float distance, unsigned int player_index) {
    INVARIANTS_ON_EXIT;

    if (state == WAITING) {
        return -1.0f;
    }

    float movement_excess = PlayerState::move(distance, player_index);
    float retval;

    BOOST_SCOPE_EXIT(&retval, &state) {
        ENSURE(state != DEAD || retval < 0.0f);
    } BOOST_SCOPE_EXIT_END

    if (state != DEAD || movement_excess < 0.0f) {
        return retval = movement_excess;
    }
    else {
        // path finding for dead ghosts:

        // destination reached, need to pick next destination
        auto respawn_node = GHOST_NODES.get_respawns().at(player_index - 1u);
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
    INVARIANTS_ON_EXIT;
    REQUIRE(state != DEAD);  // dead ghosts have no free will, they must return to the ghost pen
    PlayerState::act(action);
}

void GhostState::die() {
    INVARIANTS_ON_EXIT;
    REQUIRE(vulnerable);

    state = DEAD;
    vulnerable = false;

    // initial path finding to respawn point: which way is shortest, through origin or destination?
    ASSERT(origin);
    float origin_cost = (get_pos() - origin->get_location()).length() + GHOST_NODES.get_cost(*origin);
    float destination_cost = (get_pos() - destination->get_location()).length() + GHOST_NODES.get_cost(*destination);
    if (origin_cost < destination_cost) {
        std::swap(origin, destination);
    }
}

bool GhostState::operator==(const GhostState& o) const {
    return PlayerState::operator==(o) &&
        o.state == state;
}

const Nodes& GhostState::get_nodes() const {
    return GHOST_NODES;
}

bool GhostState::is_leaving_pen() const {
    return GHOST_NODES.is_spawn_node(origin);
}

bool GhostState::can_reverse() const {
    return state != DEAD && state != WAITING && 
        !is_leaving_pen() &&
        PlayerState::can_reverse();
}

bool GhostState::is_vulnerable() const {
    return vulnerable;
}

bool GhostState::is_dead() const {
    return state == DEAD;
}

bool GhostState::is_waiting() const {
    return state == GhostState::WAITING;
}

void GhostState::leave_pen() {
    INVARIANTS_ON_EXIT;

    REQUIRE(state == WAITING);
    state = NORMAL;
}

bool GhostState::become_invulnerable() {
    INVARIANTS_ON_EXIT;
    bool old_vulnerable = vulnerable;
    vulnerable = false;
    return old_vulnerable != vulnerable;
}

/*
 * Become vulnerable if allowed
 *
 * Returns true if vulnerability changed
 */
bool GhostState::try_become_vulnerable() {
    INVARIANTS_ON_EXIT;
    if (state == DEAD) {
        return false;
    }

    bool old_vulnerable = vulnerable;
    vulnerable = true;
    return old_vulnerable != vulnerable;
}

void GhostState::print(std::ostream& out, string prefix, string name) const {
    PlayerState::print(out, prefix, name);
    out << prefix << "const GhostState::State " << name << "_state = (GhostState::State)" << state << ";" << endl;
    out << prefix << "const bool " << name << "_vulnerable = " << vulnerable << ";" << endl;
}

void GhostState::invariants() const {
    PlayerState::invariants();

    // these invariants are part of a new internal contract; so they don't break the liskov substitution principle
    INVARIANT(!(vulnerable && state == DEAD));
}

// Note: this has little meaning other than that when it changes, a new action may be chosen (which is by crossing any grid line with offset half a tile)

}}
