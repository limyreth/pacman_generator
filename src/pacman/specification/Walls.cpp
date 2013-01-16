/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Walls.h"
#include "../Constants.h"

namespace PACMAN {
    namespace SPECIFICATION {

const bool walls[MAP_HEIGHT * MAP_WIDTH] = {
    true,  true,  true,  true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true,
    true,  false, false, false, false, false, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, false, false, false, false, false, true,
    true,  false, true,  true, true, true, false, true, true, true, true, true, false, true, true, false, true, true, true, true, true, false, true, true, true, true, false, true,
    true,  false, true,  false, false, true, false, true, false, false, false, true, false, true, true, false, true, false, false, false, true, false, true, false, false, true, false, true,
    true,  false, true,  true, true, true, false, true, true, true, true, true, false, true, true, false, true, true, true, true, true, false, true, true, true, true, false, true,
    true,  false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true,
    true,  false, true,  true, true, true, false, true, true, false, true, true, true, true, true, true, true, true, false, true, true, false, true, true, true, true, false, true,
    true,  false, true,  true, true, true, false, true, true, false, true, true, true, true, true, true, true, true, false, true, true, false, true, true, true, true, false, true,
    true,  false, false, false, false, false, false, true, true, false, false, false, false, true, true, false, false, false, false, true, true, false, false, false, false, false, false, true,
    true,  true,  true,  true, true, true, false, true, true, true, true, true, false, true, true, false, true, true, true, true, true, false, true, true, true, true, true, true,
    false, false, false, false, false, true, false, true, true, true, true, true, false, true, true, false, true, true, true, true, true, false, true, false, false, false, false, false,
    false, false, false, false, false, true, false, true, true, false, false, false, false, false, false, false, false, false, false, true, true, false, true, false, false, false, false, false,
    false, false, false, false, false, true, false, true, true, false, true, true, true, true, true, true, true, true, false, true, true, false, true, false, false, false, false, false,
    true,  true,  true,  true, true, true, false, true, true, false, true, false, false, false, false, false, false, true, false, true, true, false, true, true, true, true, true, true,
    false, false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false,
    true,  true,  true,  true, true, true, false, true, true, false, true, false, false, false, false, false, false, true, false, true, true, false, true, true, true, true, true, true,
    false, false, false, false, false, true, false, true, true, false, true, true, true, true, true, true, true, true, false, true, true, false, true, false, false, false, false, false,
    false, false, false, false, false, true, false, true, true, false, false, false, false, false, false, false, false, false, false, true, true, false, true, false, false, false, false, false,
    false, false, false, false, false, true, false, true, true, false, true, true, true, true, true, true, true, true, false, true, true, false, true, false, false, false, false, false,
    true,  true,  true,  true, true, true, false, true, true, false, true, true, true, true, true, true, true, true, false, true, true, false, true, true, true, true, true, true,
    true,  false, false, false, false, false, false, false, false, false, false, false, false, true, true, false, false, false, false, false, false, false, false, false, false, false, false, true,
    true,  false, true,  true, true, true, false, true, true, true, true, true, false, true, true, false, true, true, true, true, true, false, true, true, true, true, false, true,
    true,  false, true,  true, true, true, false, true, true, true, true, true, false, true, true, false, true, true, true, true, true, false, true, true, true, true, false, true,
    true,  false, false, false, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true, true, false, false, false, true,
    true,  true,  true,  false, true, true, false, true, true, false, true, true, true, true, true, true, true, true, false, true, true, false, true, true, false, true, true, true,
    true,  true,  true,  false, true, true, false, true, true, false, true, true, true, true, true, true, true, true, false, true, true, false, true, true, false, true, true, true,
    true,  false, false, false, false, false, false, true, true, false, false, false, false, true, true, false, false, false, false, true, true, false, false, false, false, false, false, true,
    true,  false, true,  true, true, true, true, true, true, true, true, true, false, true, true, false, true, true, true, true, true, true, true, true, true, true, false, true,
    true,  false, true,  true, true, true, true, true, true, true, true, true, false, true, true, false, true, true, true, true, true, true, true, true, true, true, false, true,
    true,  false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true,
    true,  true,  true,  true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true
};

}}
