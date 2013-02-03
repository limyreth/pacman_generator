/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "PlayerState.h"
#include "Node.h"
#include "Nodes.h"
#include "GhostNodes.h"
#include "PacmanNodes.h"
#include "../Constants.h"
#include "../util/assertion.h"

#include <algorithm>
#include <cmath>

using std::min;
using std::cout;
using std::endl;
using std::string;

namespace PACMAN {
    namespace MODEL {

// default constructor because collections want them, don't use anything
// instantiated like this, because it is utter garbage
PlayerState::PlayerState() 
{
}

PlayerState::PlayerState(const Node* origin, const Node* destination, FPoint pos)
:   pos(pos / ::PACMAN::GUI::TILE_SIZE),
    origin(origin),
    destination(destination)
{
}

PlayerState::PlayerState(const Node& initial_node) 
:   pos(initial_node.get_location()), 
    origin(NULL),
    destination(&initial_node)
{
    INVARIANTS_ON_EXIT;
}

/*
 * Move player distance_moved px towards destination, ...
 */
double PlayerState::move(double distance_moved, int player_index) {
    INVARIANTS_ON_EXIT;
    REQUIRE(distance_moved >= 0.0);
    REQUIRE(!has_reached_destination());
    REQUIRE(player_index >= 0);
    REQUIRE(player_index < PLAYER_COUNT);

    FPoint direction = destination->get_location() - pos;
    double movement_excess = distance_moved - direction.length();

    if (distance_moved > 0.0) {
        double distance_moved_towards_destination = min(direction.length(), distance_moved);

        // move towards destination
        if (get_nodes().are_connected_through_wrapping(*origin, *destination)) {
            direction = origin->get_location() - destination->get_location();
        }
        direction.normalise();
        pos += direction * distance_moved_towards_destination;

        // wrap screen when hitting left/right edge of tunnel
        if (pos.x < 0) {
            pos.x += MAP_WIDTH;
        }
        else if (pos.x >= MAP_WIDTH) {
            pos.x -= MAP_WIDTH;
        }

        if (has_reached_destination() && movement_excess > MAX_ROUNDING_ERROR && movement_excess < 0.0) {
            // deal with rounding error
            movement_excess = 0.0;
        }
    }

    ENSURE(has_reached_destination() == (movement_excess >= 0.0));
    return movement_excess;
}

void PlayerState::act(Action action) {
    INVARIANTS_ON_EXIT;
    REQUIRE(action >= 0);
    REQUIRE(action < get_action_count());

    action = external_to_internal(action);

    // destination reached
    // consume the next action
    auto new_destination = destination->get_neighbours().at(action);
    ASSERT(new_destination != origin);
    origin = destination;
    destination = new_destination;

    ENSURE(!has_reached_destination());
}

Action PlayerState::external_to_internal(Action external) const {
    REQUIRE(external >= 0);
    REQUIRE(external < get_action_count());

    Action internal = -1;
    while (external >= 0) {
        ++internal;
        if (!is_reversing_action(internal)) {
            external--;
        }
    }

    ENSURE(internal >= 0);
    ENSURE(internal < destination->get_neighbours().size());
    ENSURE(!is_reversing_action(internal));
    return internal;
}

Action PlayerState::internal_to_external(Action internal) const {
    REQUIRE(internal >= 0);
    REQUIRE(internal < destination->get_neighbours().size());
    REQUIRE(!is_reversing_action(internal));

    auto external = internal;
    for (int i = 0; i <= internal; ++i) {
        if (is_reversing_action(i)) {
            external--;
        }
    }

    ENSURE(external >= 0);
    ENSURE(external < get_action_count());
    return external;
}

bool PlayerState::has_reached_destination() const {
    return pos == destination->get_location();
}

IPoint PlayerState::get_tile_pos() const {
    IPoint tile_pos(pos.x, pos.y);
    return tile_pos;
}

unsigned char PlayerState::get_action_count() const {
    if (!has_reached_destination()) {
        return 0;
    }
    else {
        int count = 0;
        for (int i = 0; i < destination->get_neighbours().size(); ++i) {
            if (!is_reversing_action(i)) {
                count++;
            }
        }
        return count;
    }
}

/*
 * Returns true if said internal action reverses the move we just made
 */
bool PlayerState::is_reversing_action(Action action) const {
    REQUIRE(action >= 0);
    REQUIRE(action < destination->get_neighbours().size());

    if (origin) {
        auto new_destination = destination->get_neighbours().at(action);
        if (origin == new_destination) {
            return true;
        }

        const auto& new_neighbours = new_destination->get_neighbours(); // Note: this probably only applies to pacman
        if (std::find(new_neighbours.begin(), new_neighbours.end(), origin) != new_neighbours.end()) {
            return true;
        }
    }
    return false;
}

/*
 * Gets action that moves most along the desired direction
 */
Action PlayerState::get_action_along_direction(Direction::Type direction_) const {
    REQUIRE(get_action_count() > 0);

    if (direction_ == Direction::ANY)
        return 0;

    auto direction = DIRECTIONS[(int)direction_];

    double best_dot_prod = -1.0; // worst = -1, best = 1
    Action best_action = -1;
    for (int i=0; i < destination->get_neighbours().size(); ++i) {
        if (is_reversing_action(i)) {
            continue;
        }

        auto neighbour = destination->get_neighbours()[i];
        auto dir = neighbour->get_location() - destination->get_location();
        dir.normalise();
        if (get_nodes().are_connected_through_wrapping(*destination, *neighbour)) {
            dir = -dir;
        }

        double dot_prod = dir.dot_product(direction);
        ASSERT(dot_prod >= -1.0);
        ASSERT(dot_prod <= 1.0);

        if (dot_prod >= best_dot_prod) {
            best_action = i;
            best_dot_prod = dot_prod;
        }
    }

    best_action = internal_to_external(best_action);

    ENSURE(best_action < get_action_count());
    return best_action;
}

bool PlayerState::operator==(const PlayerState& o) const {
    return (o.pos - pos).length() < MAX_ROUNDING_ERROR &&
        o.origin == origin &&
        o.destination == destination;
}

void PlayerState::invariants() const {
    INVARIANT(pos.x >= 0);
    INVARIANT(pos.y >= 0);
    INVARIANT(pos.x < MAP_WIDTH);
    INVARIANT(pos.y < MAP_HEIGHT);
    INVARIANT(destination != NULL);
}

const FPoint& PlayerState::get_pos() const {
    return pos;
}

bool PlayerState::can_reverse() const {
    return origin != NULL; // = call act() at least once after player (re)spawn
}

void PlayerState::reverse() {
    INVARIANTS_ON_EXIT;
    REQUIRE(can_reverse());
    std::swap(origin, destination);
}

void PlayerState::print(std::ostream& out, string prefix, string name) const {
    out << prefix << "const int " << name << "_origin = " << get_nodes().get_id(origin) << ";" << endl
        << prefix << "const int " << name << "_destination = " << get_nodes().get_id(destination) << ";" << endl
        << prefix << "const FPoint " << name << "_pos" << pos << ";" << endl;
}

bool PlayerState::is_in_tunnel() const {
    auto tpos = get_tile_pos();
    return tpos.y == 14 && ((tpos.x >= 0 && tpos.x <= 5) || (tpos.x >= MAP_WIDTH - 6 && tpos.x <= MAP_WIDTH - 1));
}

// Note: reversing direction between intersections is a legal action and a
// perfect play player might actually make use of that. E.g. consider this path between intersections:
// Dot Dot Dot 
// => Pac Dot Dot 
// => None Dot Ghost (pacman reversed because it had to run) 
// => None Dot Pac (pacman now approaches from the right)
// => Ghost Pac None (pacman now cleared this path, which would not have been possible without reversing)

}}
