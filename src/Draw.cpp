/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Draw.h"

extern Log logtxt;
extern App app;
extern Game game;
extern Settings settings;

void scale_to_tile_size(shared_ptr<SDL_Surface>& surface) {
    double zoomx = (double) settings.tilesize / surface->w;
    double zoomy = (double) settings.tilesize / surface->h;
    int dw, dh;
    zoomSurfaceSize(surface->w, surface->h, zoomx, zoomy, &dw, &dh);
    assert(dw == settings.tilesize);
    assert(dh == settings.tilesize);
    assert(settings.tilesize==20);
    surface.reset(zoomSurface(surface.get(), zoomx, zoomy, 0), SDL_FreeSurface);
}
