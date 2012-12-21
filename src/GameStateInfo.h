/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "Constants.h"

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

namespace PACMAN {
    namespace MODEL {

        typedef char Action;

        struct LegalActions {
            unsigned char count; // legal actions are [0, count-1]. If count==-1, only the previously given action is legal.
            Action reverse_action;  // which action is the reverse action, -1 if none
        };

    }
}
