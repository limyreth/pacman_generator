/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Pacman.h"
#include "Draw.h"
#include "../model/PacmanState.h"
#include "../util/Log.h"
#include "../util/error.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

using ::PACMAN::MODEL::TILE_SIZE;
using std::shared_ptr;

namespace PACMAN {
    namespace GUI {

void Pacman::Draw(int ix, int iy, int obj, int type) {
    SDL_Rect pos;

    pos.x=ix;
    pos.y=iy;

    SDL_BlitSurface(pacEl[3].get(),NULL,buf.get(),&pos);
}

void Pacman::reset() {
    animcounter=0;
}

void Pacman::Draw(const MODEL::PacmanState state) {

    int i;
    SDL_Rect pos;

    //calculate displayed animation frame from animcounter.. abs is not the right function
    //there's probably a better way to handle this:
    if ( animcounter < 2 ) i=0;
    else if ( animcounter >= 2 && animcounter < 4 ) i=1;
    else if ( animcounter >= 4 && animcounter < 6 ) i=2;
    else if ( animcounter >= 6 && animcounter < 8 ) i=3;
    else if ( animcounter >= 8 && animcounter < 10 ) i=4;
    else if ( animcounter >= 10 && animcounter < 12 ) i=5;
    else if ( animcounter >= 12 && animcounter < 14 ) i=6;
    else if ( animcounter >= 14 && animcounter < 16 ) i=7;
    else if ( animcounter >= 16 && animcounter < 18 ) i=7;
    else if ( animcounter >= 18 && animcounter < 20 ) i=6;
    else if ( animcounter >= 20 && animcounter < 22 ) i=5;
    else if ( animcounter >= 22 && animcounter < 24 ) i=4;
    else if ( animcounter >= 24 && animcounter < 26 ) i=3;
    else if ( animcounter >= 26 && animcounter < 28 ) i=2;
    else if ( animcounter >= 28 && animcounter < 30 ) i=1;
    else if ( animcounter >= 30 && animcounter < 32 ) i=0;
    else i=0; //avoid compiler warning

    // center the image on our current location
    FPoint real_pos = state.get_pixel_pos();
    pos.x = real_pos.x - PLAYER_SIZE/2;
    pos.y = real_pos.y - PLAYER_SIZE/2;

    // TODO render correct direction (requires old pacman state as well)
    int dx = 0;
    int dy = 0;
    if (dx == 1 && dy == 0) {	//right
        SDL_BlitSurface(pacEl[i].get(),NULL,buf.get(),&pos);
    }
    else if (dx == -1 && dy == 0) {	//left
        SDL_BlitSurface(pacElRot[i][1].get(),NULL,buf.get(),&pos);
    }
    else if (dx == 0 && dy == -1) {	//up
        SDL_BlitSurface(pacElRot[i][2].get(),NULL,buf.get(),&pos);
    }
    else if (dx == 0 && dy == 1) {	//down
        SDL_BlitSurface(pacElRot[i][0].get(),NULL,buf.get(),&pos);
    }
    else if (dx == 0 && dy == 0) {	//init position
        SDL_BlitSurface(pacEl[i].get(),NULL,buf.get(),&pos);
    }

    if (!paused) {
        if (animcounter == 31) animcounter = 0;
        else animcounter++;
    }
}


void Pacman::LoadTextures(std::string path) {

    int i,j;
    std::string num[10];
    SDL_PixelFormat *fmt;

    for (i=0;i<10;i++)
        num[i]='0'+i;

    for (i=0;i<NUMPACANIM;i++) {
        pacEl[i].reset(IMG_Load((path + "pac" + num[i] + ".png").c_str()), SDL_FreeSurface);

        if ( !pacEl[i] )
            throw_exception("Failed to load pacman texture: " + num[i]);

        fmt = pacEl[i]->format;
        SDL_SetColorKey(pacEl[i].get(),SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(fmt,255,0,255));
        scale_to_size(pacEl[i], PLAYER_SIZE);

        //cache rotated sprites
        for (j=0;j<3;j++) {
            if (j==1)
                pacElRot[i][j]=Rotate(pacEl[i],0,-1,1);
            else
                pacElRot[i][j]=Rotate(pacEl[i],360-(j+1)*90);
        }
    }


    logtxt.print("Pacman textures loaded");
}

Pacman::Pacman(shared_ptr<SDL_Surface> buf, int os)
:   Object(buf, os),
    animcounter(0)
{
}

}}
