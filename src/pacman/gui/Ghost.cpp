/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Ghost.h"
#include "Draw.h"
#include "../model/GhostState.h"
#include "../util/error.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

using ::PACMAN::MODEL::GhostState;
using std::shared_ptr;

namespace PACMAN {
    namespace GUI {

void Ghost::Draw(int ix, int iy, int obj, int type) {
    SDL_Rect pos;

    pos.x = ix;
    pos.y = iy;

    SDL_BlitSurface(ghostEl[0].get(),NULL,buf.get(),&pos);
}

void Ghost::reset() {
    animcounter=0;
}

void Ghost::Draw(const MODEL::GhostState& current) {
    SDL_Rect pos;

    // center the image on our current location
    FPoint real_pos = current.get_pixel_pos() * TILE_SIZE;
    pos.x = real_pos.x - PLAYER_SIZE/2;
    pos.y = real_pos.y - PLAYER_SIZE/2;

    if (current.is_vulnerable()) {
        SDL_BlitSurface(ghostEl[1].get(),NULL,buf.get(),&pos);
    }
    else if (current.is_dead()) {
        SDL_BlitSurface(ghostEl[3].get(),NULL,buf.get(),&pos);
    }
    else {
        SDL_BlitSurface(ghostEl[0].get(),NULL,buf.get(),&pos);
    }
}

void Ghost::LoadTextures(std::string path) {
    std::string files[5];
    SDL_PixelFormat *fmt;

    files[0]=path + "baddie" + filename + ".png";
    files[1]=path + "baddie" + filename + "vuln.png";
    files[2]=path + "baddie" + filename + "warn.png";
    files[3]=path + "baddie_dead.png";

    for (int i = 0; i<4; i++) {
        ghostEl[i].reset(IMG_Load(files[i].c_str()), SDL_FreeSurface);
        if ( !ghostEl[i] )
            throw_exception("Failed to load ghost texture: " + files[i]);

        fmt=ghostEl[i]->format;
        SDL_SetColorKey(ghostEl[i].get(),SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(fmt,255,0,255));
        scale_to_size(ghostEl[i], PLAYER_SIZE);
    }
}

Ghost::Ghost(shared_ptr<SDL_Surface> buf, int os, std::string fn)
:   Object( buf, os),
    animcounter(0),
    filename(fn)
{
}

}}
