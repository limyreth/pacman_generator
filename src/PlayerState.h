/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "Point.h"
#include "GameStateInfo.h"

class Node;

class PlayerState
{
public:
    PlayerState();
    PlayerState(const Node* initial_node);
    void move(double distance_moved, Action next_action, Actions legal_actions);
    IPoint get_tile_pos() const;

    inline FPoint get_pixel_pos() const {
        return pos;
    }

    void get_initial_legal_actions(Actions legal_actions) const;

private:
    void get_legal_actions(Actions legal_actions, const Node* old_destination) const;
    void get_repeat_actions(Action action, Actions legal_actions) const;

private:
    FPoint pos;  // current position in pixels
    const Node* destination;  // move towards this node
};
