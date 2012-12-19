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

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class Node;
class SDL_Surface;

// these are choice nodes for pacman/ghosts
class Nodes
{
public:
    Nodes();
    virtual ~Nodes();

    void draw(shared_ptr<SDL_Surface> buffer);

protected:
    void init(const int* walls);
    std::vector<Node*> nodes;

    void assert_valid(const std::vector<Node*>& nodes);
    void assert_valid(const Node* node);

    double get_branching_factor(const std::vector<Node*>& nodes);
};
