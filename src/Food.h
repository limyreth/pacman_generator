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

namespace PACMAN {

    namespace SPECIFICATION {

        namespace Food {
            enum Type : unsigned char {
                NONE,
                DOT,
                ENERGIZER
            };
        }
        typedef Food::Type Foods[MAP_WIDTH * MAP_HEIGHT];

    }
}
