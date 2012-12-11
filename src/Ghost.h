/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "Object.h"

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class SDL_Surface;
class GhostState;

class Ghost :
	public Object
{
public:
    Ghost(shared_ptr<SDL_Surface> buf, int os, std::string fn);

    void Draw(const GhostState& current);
    void Draw(int ix, int iy, int obj=0, int type=0) ;
    void LoadTextures(std::string path);
    void reset();

private:
    int animcounter;

    shared_ptr<SDL_Surface>
            ghostEl[5];

    std::string
            filename;
};
