/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "BckgrObj.h"
#include "Draw.h"
#include "../util/error.h"
#include "../util/util.h"

#include <SDL/SDL_image.h>

using namespace ::PACMAN::SPECIFICATION;
using std::shared_ptr;

namespace PACMAN {
    namespace GUI {

BckgrObj::BckgrObj(shared_ptr<SDL_Surface> buffer, int os)
    :	Object(buffer, os)
{
    fruit_pos.w = fruit_pos.h = PLAYER_SIZE;
    fruit_pos.x = FRUIT_POS.x - fruit_pos.w / 2.0;
    fruit_pos.y = FRUIT_POS.y - fruit_pos.h / 2.0;
}

void BckgrObj::Draw(int ix, int iy, int obj, int type) {
    assert(false);
}

void BckgrObj::Draw(const Foods foods, bool fruit_spawned, bool show_food) {
    SDL_FillRect(buf.get(), NULL, 0);

    // DRAW MAP
    SDL_BlitSurface(map.get(), NULL, buf.get(), NULL);

    // DRAW OBJECTS
    for (int j=0;j<MAP_HEIGHT;j++) {
        for (int i=0; i<MAP_WIDTH; i++) {

            SDL_Rect pos;
            pos.x=i*TILE_SIZE;
            pos.y=j*TILE_SIZE;
            pos.h=TILE_SIZE;
            pos.w=TILE_SIZE;

            if (show_food) {
                if (foods.at(j*MAP_WIDTH+i)==Food::DOT) {
                    SDL_BlitSurface(objEl[0].get(), NULL, buf.get(), &pos);
                }
                else if (foods.at(j*MAP_WIDTH+i)==Food::ENERGIZER) {
                    SDL_BlitSurface(objEl[1].get(), NULL, buf.get(), &pos);
                }
            }
        }
    }
    if (fruit_spawned) {
        SDL_BlitSurface(objEl[2].get(), NULL, buf.get(), &fruit_pos);
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
        if (i != 2) {
            scale_to_size(objEl[i], TILE_SIZE);
        }
        else {
            scale_to_size(objEl[i], PLAYER_SIZE);
        }
    }
}

}}
