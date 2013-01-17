/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "BckgrObj.h"
#include "../Error.h"
#include "Draw.h"
#include "../Log.h"
#include "../Utility.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

using namespace ::PACMAN::SPECIFICATION;

namespace PACMAN {
    namespace GUI {

void BckgrObj::Draw(int ix, int iy, int obj, int type, int alp) {
    SDL_Rect pos;

    pos.x=ix;
    pos.y=iy;
    pos.h=pos.w=TILE_SIZE;

    if (type == 1) {
        SDL_SetAlpha(objEl[obj].get(),SDL_SRCALPHA|SDL_RLEACCEL,alp);
        SDL_BlitSurface(objEl[obj].get(),NULL,buf.get(),&pos);
    }
    else {
        assert(false);
    }
}

void BckgrObj::Draw(int ix, int iy, int obj, int type) {
    Draw(ix,iy,obj,type,255);
}

void BckgrObj::Draw(const Foods foods) {
    int i, j;
    SDL_Rect pos;

    objcounter = 0;

    SDL_FillRect(buf.get(), NULL, 0);

    // DRAW MAP
    SDL_SetAlpha(map.get(), SDL_SRCALPHA | SDL_RLEACCEL, alpha);
    SDL_BlitSurface(map.get(), NULL, buf.get(), NULL);

    // DRAW OBJECTS
    for (j=0;j<MAP_HEIGHT;j++) {
        for (i=0; i<MAP_WIDTH; i++) {

            pos.x=i*TILE_SIZE;
            pos.y=j*TILE_SIZE;
            pos.h=TILE_SIZE;
            pos.w=TILE_SIZE;

            if (foods[j*MAP_WIDTH+i]==Food::DOT) {
                SDL_SetAlpha(objEl[0].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(objEl[0].get(), NULL, buf.get(), &pos);
                objcounter++;
            }
            else if (foods[j*MAP_WIDTH+i]==Food::ENERGIZER) {
                SDL_SetAlpha(objEl[1].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(objEl[1].get(), NULL, buf.get(), &pos);
                objcounter++;
            }
            /*else if (foods[j*width+i]==3 && specialspawned && !specialeaten) {	// fruit TODO
                SDL_SetAlpha(objEl[2].get(),SDL_SRCALPHA,fruitalpha);
                SDL_BlitSurface(objEl[2].get(), NULL, buf.get(), &pos);
                objcounter++;
            }*/
        }
    }


}

void BckgrObj::LoadTextures(std::string path) {
    SDL_PixelFormat *fmt;

    {
        // load map sprite
        map.reset(IMG_Load((path + "map.png").c_str()), SDL_FreeSurface);
        if (map == NULL )
            throw_exception("Failed to load map texture");

        //get pixel format from surface
        fmt = map->format;

        //set the transparent color key to RGB 255 0 255
        SDL_SetColorKey(map.get(), SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(fmt,255,0,255));

        // scale to fit
        scale_to_size(map, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE);
    }

    // object sprites
    for (int i=0; i<3; i++) {
        objEl[i].reset(IMG_Load((path + "o" + to_string(i) + ".png").c_str()), SDL_FreeSurface);
        if ( objEl[i] == NULL )
            throw_exception(to_string(i) + "Failed to load object texture");

        //get pixel format from surface
        fmt=objEl[i]->format;

        //set the transparent color key to RGB 255 0 255
        SDL_SetColorKey(objEl[i].get(),SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(fmt,255,0,255));

        // scale it to tile size
        scale_to_size(objEl[i], TILE_SIZE);
    }

    logtxt.print("Field textures loaded");
}

BckgrObj::BckgrObj( shared_ptr<SDL_Surface> buffer, int os)
    :	Object( buffer, os),
    objcounter(0)
{
}

}}
