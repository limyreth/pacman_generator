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
#include "../Constants.h"
#include <assert.h>
#include "../Utility.h"

namespace PACMAN {
    namespace MODEL {

// default constructor because collections want them, don't use anything
// instantiated like this, because it is utter garbage
PlayerState::PlayerState() 
{
}

PlayerState::PlayerState(const Node* initial_node) 
:   pos(initial_node->location), 
    must_repeat_previous_action(false),
    origin(NULL),
    destination(initial_node)
{
    assert(pos.x >= 0);
    assert(pos.y >= 0);
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
    FPoint direction = destination->location - pos;

    if (direction.length() <= distance_moved) {
        must_repeat_previous_action = false;

        // destination reached
        // consume the next action
        origin = destination;
        destination = destination->neighbours.at(next_action);
        // TODO move towards new destination for the remainder: distance_moved - direction.length
        return;
    }
    else {
        must_repeat_previous_action = true;

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
}

IPoint PlayerState::get_tile_pos() const {
    assert(pos.x >= 0);
    assert(pos.y >= 0);
    assert(pos.x <= MAP_WIDTH * TILE_SIZE);
    assert(pos.y <= MAP_HEIGHT * TILE_SIZE);
    return IPoint(pos.x / TILE_SIZE, pos.y / TILE_SIZE);
}

void PlayerState::get_legal_actions(LegalActions& legal_actions) const {
    if (must_repeat_previous_action) {
        legal_actions.count = -1;
        legal_actions.reverse_action = -1;
    }
    else {
        legal_actions.count = destination->neighbours.size();

        legal_actions.reverse_action = -1;
        if (origin) {
            for (Action i=0; i < destination->neighbours.size(); ++i) {
                if (origin == destination->neighbours.at(i)) {
                    legal_actions.reverse_action = i;
                    break;
                }
            }
        }
    }
}

/*
 * Gets action that moves most along the desired direction
 */
Action PlayerState::get_action_along_direction(Direction::Type direction_) const {
    if (direction_ == Direction::ANY)
        return 0;

    auto direction = DIRECTIONS[(int)direction_];
    assert(direction.length() == 1.0);

    double best_dot_prod = -1.0; // worst = -1, best = 1
    Action best_action = -1;
    for (int i=0; i < destination->neighbours.size(); ++i) {
        auto dir = destination->neighbours[i]->location - destination->location;
        dir.normalise();

        double dot_prod = dir.dot_product(direction);
        assert(dot_prod >= -1.0);
        assert(dot_prod <= 1.0);

        if (dot_prod >= best_dot_prod) {
            best_action = i;
        }
    }
    return best_action;
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
