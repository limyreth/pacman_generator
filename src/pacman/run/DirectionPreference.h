/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "Input.h"
#include <pacman/util/Directions.h>

namespace PACMAN {
    namespace RUN {

        class DirectionPreference
        {
        public:
            virtual Direction::Type get_preferred_direction() = 0;
        };

    }
}
