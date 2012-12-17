/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <vector>
#include "Point.h"

#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

// these are choice nodes for pacman/ghosts
class Node
{
public:
    Node(FPoint location);

public:
    FPoint location; // TODO player locations should also be FPoint
    std::vector<Node*> neighbours;
};
