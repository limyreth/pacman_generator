/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Directions.h"

Directions DIRECTIONS = {
    FPoint(0, -1), // North; y-axis points towards the bottom of the screen
    FPoint(1, 0), // East
    FPoint(0, 1), // South
    FPoint(-1, 0) // West
};
