/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Object.h"

#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>

using std::shared_ptr;

namespace PACMAN {
    namespace GUI {

shared_ptr<SDL_Surface> Object::Rotate(shared_ptr<SDL_Surface> src, int angle, double zoomx, double zoomy) {
    if (!(angle < 360 && angle >= 0 && angle % 90 == 0))
        return src;

    int turns = (360 - angle) / 90;

    shared_ptr<SDL_Surface> zoomedSurface(
            zoomSurface(src.get(), zoomx, zoomy, SMOOTHING_OFF),
            SDL_FreeSurface);

    /* for some reason, if we don't exit here without rotation we get an invisible surface.. */
    if (turns % 4 == 0)
        return zoomedSurface;

    shared_ptr<SDL_Surface> rotatedSurface(
            rotateSurface90Degrees(zoomedSurface.get(), turns),
            SDL_FreeSurface);

    return rotatedSurface;
}

}}
