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
#include "../Constants.h"
#include "../Utility.h"
#include "../util/assertion.h"
#include "../util/serialization.h"
#include <cmath>

using std::min;
using std::endl;

namespace PACMAN {
    namespace MODEL {

// default constructor because collections want them, don't use anything
// instantiated like this, because it is utter garbage
PlayerState::PlayerState() 
{
}

PlayerState::PlayerState(const Node* initial_node) 
:   pos(initial_node->get_location()), 
    must_repeat_previous_action(false),
    origin(NULL),
    destination(initial_node)
{
    INVARIANTS_ON_EXIT;
    REQUIRE(initial_node);
}

PlayerState::PlayerState(std::istream& in, const Nodes& nodes) {
    INVARIANTS_ON_EXIT;
    read(in, pos.x);
    read(in, pos.y);
    read(in, must_repeat_previous_action);
    origin = nodes.load(in);
    destination = nodes.load(in);
}

/*
 * Move player distance_moved px towards destination, ...
 * 
 * If destination reached, pick new one by next_action.
 *
 * precondition: next_action is one of previously acquired legal_actions
 * postcondition: legal_actions contains the legal actions for the next move.
 */
void PlayerState::move(double distance_moved, Action next_action) {
    INVARIANTS_ON_EXIT;
    REQUIRE(distance_moved >= 0.0);
    REQUIRE(next_action >= 0);
    REQUIRE(next_action < destination->get_neighbours().size());

    FPoint direction = destination->get_location() - pos;
    double distance_moved_towards_destination = min(direction.length(), distance_moved);
    double distance_moved_towards_new_destination = distance_moved - distance_moved_towards_destination;

    // move towards destination
    if (distance_moved_towards_destination > 0.0) {
        must_repeat_previous_action = true;
        move(distance_moved_towards_destination);
    }

    // if movement left, pick new destination and move towards that as well
    if (distance_moved_towards_new_destination > 0.0) {
        must_repeat_previous_action = false;

        // destination reached
        // consume the next action
        origin = destination;
        destination = destination->get_neighbours().at(next_action);
        move(distance_moved_towards_new_destination);
    }
}

void PlayerState::move(double distance_moved) {
    INVARIANTS_ON_EXIT;
    REQUIRE(distance_moved >= 0.0);

    FPoint direction = destination->get_location() - pos;
    direction.normalise();
    pos += direction * distance_moved;

    // wrap screen when hitting left/right edge of tunnel
    auto tpos = get_tile_pos();
    if (tpos.x < 0) {
        pos.x = MAP_WIDTH * TILE_SIZE - pos.x;
    }
    else if (tpos.x >= MAP_WIDTH) {
        pos.x -= MAP_WIDTH * TILE_SIZE;
    }
}

IPoint PlayerState::get_tile_pos() const {
    return IPoint(pos.x / TILE_SIZE, pos.y / TILE_SIZE);
}

LegalActions PlayerState::get_legal_actions() const {
    LegalActions legal_actions;
    if (must_repeat_previous_action) {
        legal_actions.count = 0;
        legal_actions.reverse_action = -1;
    }
    else {
        legal_actions.count = destination->get_neighbours().size();

        legal_actions.reverse_action = -1;
        if (origin) {
            for (Action i=0; i < destination->get_neighbours().size(); ++i) {
                if (origin == destination->get_neighbours().at(i)) {
                    legal_actions.reverse_action = i;
                    break;
                }
            }
        }

        ENSURE(legal_actions.count > 0);
    }
    ENSURE(legal_actions.count <= MAX_ACTION_COUNT);
    return legal_actions;
}

/*
 * Gets action that moves most along the desired direction
 */
Action PlayerState::get_action_along_direction(Direction::Type direction_) const {
    if (direction_ == Direction::ANY)
        return 0;

    auto direction = DIRECTIONS[(int)direction_];

    double best_dot_prod = -1.0; // worst = -1, best = 1
    Action best_action = -1;
    for (int i=0; i < destination->get_neighbours().size(); ++i) {
        auto dir = destination->get_neighbours()[i]->get_location() - destination->get_location();
        dir.normalise();

        double dot_prod = dir.dot_product(direction);
        ASSERT(dot_prod >= -1.0);
        ASSERT(dot_prod <= 1.0);

        if (dot_prod >= best_dot_prod) {
            best_action = i;
            best_dot_prod = dot_prod;
        }
    }
    return best_action;
}

void PlayerState::save(std::ostream& out, const Nodes& nodes) const {
    write(out, pos);
    write(out, must_repeat_previous_action);
    nodes.save(out, origin);
    nodes.save(out, destination);
}

void PlayerState::invariants() const {
    INVARIANT(pos.x >= 0);
    INVARIANT(pos.y >= 0);
    INVARIANT(pos.x <= MAP_WIDTH * TILE_SIZE);
    INVARIANT(pos.y <= MAP_HEIGHT * TILE_SIZE);
}

// Note: reversing direction between intersections is a legal action and a
// perfect play player might actually make use of that. E.g. consider this path between intersections:
// Dot Dot Dot 
// => Pac Dot Dot 
// => None Dot Ghost (pacman reversed because it had to run) 
// => None Dot Pac (pacman now approaches from the right)
// => Ghost Pac None (pacman now cleared this path, which would not have been possible without reversing)
//
// Reversing is usually not the best action though, so we return it as the last possible legal action (in hope of it getting pruned)
// TODO might still want to allow a search without reversal though, as it'll probably be a lot quicker to find a solution, although we can't be sure that solution is perfect

    }
}
