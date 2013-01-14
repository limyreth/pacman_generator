/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "../model/Action.h"

namespace PACMAN {

    namespace GENERATOR {

        struct ChoiceNode {
            // the move from this node to the next
            MODEL::Action action;  

            // index of player making the move
            int player;  

            // alpha or beta value. Depends on player.
            int alpha_beta;

            bool operator==(const ChoiceNode& other) const {
                return other.action == action &&
                    other.player == player &&
                    other.alpha_beta == alpha_beta;
            }
        };

    }
}
