/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Draw.h"
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>

namespace PACMAN {
    namespace GUI {

/*
 * Rendering notes: http://home.comcast.net/~jpittman2/pacman/pacmandossier.html#CH3_What_Tile_Am_I_In
 *
 * - Walls are 2 tiles wide.
 * - Ghosts and pacman are logically in one tile (their center point is used).
 *   Their body is drawn around that center and has a size of nearly 2 tiles.
 */

void scale_to_size(shared_ptr<SDL_Surface>& surface, double size) {
    double zoomx = (double) size / surface->w;
    double zoomy = (double) size / surface->h;
    int dw, dh;
    zoomSurfaceSize(surface->w, surface->h, zoomx, zoomy, &dw, &dh);
    surface.reset(zoomSurface(surface.get(), zoomx, zoomy, 0), SDL_FreeSurface);
}

}}
