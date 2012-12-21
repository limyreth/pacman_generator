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
#include "Constants.h"
#include <assert.h>
#include "Utility.h"

// default constructor because collections want them, don't use anything
// instantiated like this, because it is utter garbage
PlayerState::PlayerState() 
{
}

PlayerState::PlayerState(const Node* initial_node) 
:   pos(initial_node->location), destination(initial_node)
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
void PlayerState::move(double distance_moved, Action next_action, LegalActions& legal_actions) {
    FPoint direction = destination->location - pos;

    if (direction.length() <= distance_moved) {
        // destination reached
        // consume the next action
        auto old_destination = destination;
        destination = destination->neighbours.at(next_action);
        get_legal_actions(legal_actions, old_destination);
        // TODO move towards new destination for the remainder: distance_moved - direction.length
        return;
    }
    else {
        // force to do same action again next tick
        get_repeat_actions(next_action, legal_actions);

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

void PlayerState::get_initial_legal_actions(LegalActions& legal_actions) const {
    legal_actions.count = destination->neighbours.size();
    legal_actions.reverse_action = -1;
}

void PlayerState::get_legal_actions(LegalActions& legal_actions, const Node* old_destination) const {
    get_initial_legal_actions(legal_actions);

    // order reverse direction last (it's likely the wrong thing to do)
    assert(old_destination);
    for (Action i=0; i < destination->neighbours.size(); ++i) {
        if (old_destination == destination->neighbours.at(i)) {
            legal_actions.reverse_action = i;
            break;
        }
    }
}

/*
 * Sets action as only legal action
 */
void PlayerState::get_repeat_actions(Action action, LegalActions& legal_actions) const {
    legal_actions.count = -1;
    legal_actions.reverse_action = -1;
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
