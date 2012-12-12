/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "PacmanState.h"
#include "Utility.h"
#include "Directions.h"

PacmanState::PacmanState(IPoint spawn_pos)
:   PlayerState(spawn_pos)
{
}

// TODO need to move at twice the speed when cornering
bool PacmanState::is_cornering(Action action) const {
    return !is_basic(action);
}

IPoint PacmanState::get_bound_pos(FPoint direction) const {
    return get_grid_pos(get_pixel_pos() + direction * PLAYER_SIZE / 2.0);
}
bool PacmanState::must_continue(Action action, const PlayerState* old) const {
    if (!old)
        return false;

    if (is_cornering(action)) {
        std::cout << "cornering" << std::endl;
        // continue until crossing a cell bound in the half-grid
        std::cout << get_half_grid_pos() << std::endl
            << old->get_half_grid_pos() << std::endl;
        return get_half_grid_pos() == old->get_half_grid_pos();
    }
    else {
        // continue until one of our bounds crosses a grid cell bound
        PacmanState* oldp = (PacmanState*)old;
        FPoint dir = action_to_direction(action);
        if (get_bound_pos(dir) != oldp->get_bound_pos(dir))
            return false;
        if (get_bound_pos(-dir) != oldp->get_bound_pos(-dir))
            return false;
        else
            return true;
    }
}

//TODO give playerState ... func
void PacmanState::get_legal_actions(const int* walls, Action action, Actions legal_actions, const PlayerState* old) {

    if (must_continue(action, old)) {
        std::cout << get_half_grid_pos() << std::endl;
        std::cout << "c";
        // Next action has to be the same as current action
        legal_actions[0] = action;
        for (int i=1; i<ACTION_COUNT; ++i) {
            legal_actions[i] = -1;
        }
    }
    else {
        std::cout << "n";
        // TODO cornering needs to start when pacman's bounds hit the edge of the next tile, not pacman's center
        // Any nonobstructed path is fine
        IPoint tpos = get_tile_pos() + action_to_direction(action);
        for (int i=0; i<ACTION_COUNT; ++i) {
            Action new_action = BASIC_ACTIONS[i];
            IPoint new_tpos = tpos + action_to_direction(new_action);

            bool is_legal_tpos = walls[at(new_tpos)] == 0 || new_tpos.x < 0 || new_tpos.x == MAP_WIDTH;
            if (is_legal_tpos) {
                if (is_basic(action) && are_perpendicular(action, new_action)) {
                    legal_actions[i] = action | new_action;
                }
                else {
                    legal_actions[i] = new_action;
                }
            }
            else {
                legal_actions[i] = 0;
            }
        }
        // TODO order reverse direction as last (swap its value with that of the last)
    }
}

