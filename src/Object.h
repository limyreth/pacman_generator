/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

#include "Constants.h"

class SDL_Surface;

class Object
{
public:
    Object(shared_ptr<SDL_Surface> buffer, int os )
    :	buf(buffer),
            offset(os),
            paused(true),
            alpha(255)
    {
    }

    virtual ~Object() {}

    void setPaused(bool b) { paused = b; }
    void setAlpha(int a) { alpha = a; }

    virtual void Draw(int ix, int iy, int obj=3, int type=1)=0;
    virtual void LoadTextures(std::string path)=0;

    virtual shared_ptr<SDL_Surface> Rotate(shared_ptr<SDL_Surface> src, int angle, double zoomx=1, double zoomy=1);
protected:
    // drawing size of ghost/pacman
    static const int PLAYER_SIZE = 2.0 * TILE_SIZE * 0.8;

    shared_ptr<SDL_Surface>
            buf;

    const int
            offset;

    bool
            paused;

    int
            alpha;
};
