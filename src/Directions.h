/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "GameStateInfo.h"
#include "Point.h"

extern const Action BASIC_ACTIONS[];

FPoint action_to_direction(Action action);
// TODO bool is_opposite_direction(FPoint)
// TODO bool are_perpendicular(FPoint, FPoint)
