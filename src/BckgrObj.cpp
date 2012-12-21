/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "BckgrObj.h"
#include "Error.h"
#include "Draw.h"
#include "Log.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

namespace PACMAN {
    namespace GUI {

using namespace SPECIFICATION;

void BckgrObj::Draw(int ix, int iy, int obj, int type, int alp) {
    SDL_Rect pos;

    pos.x=ix;
    pos.y=iy;
    pos.h=pos.w=20;

    if (type == 1) {
        SDL_SetAlpha(objEl[obj].get(),SDL_SRCALPHA|SDL_RLEACCEL,alp);
        SDL_BlitSurface(objEl[obj].get(),NULL,buf.get(),&pos);
    }
    else {
        SDL_SetAlpha(mapEl[obj].get(),SDL_SRCALPHA|SDL_RLEACCEL,alp);
        SDL_BlitSurface(mapEl[obj].get(),NULL,buf.get(),&pos);
    }
}

void BckgrObj::Draw(int ix, int iy, int obj, int type) {
    Draw(ix,iy,obj,type,255);
}

void BckgrObj::setFruitAlpha(int a) {
    fruitalpha = a;
}

void BckgrObj::Draw(const int* walls, const Foods foods) {
    int height,
        width,
        i,
        j;
    SDL_Rect pos;

    height = MAP_HEIGHT;
    width = MAP_WIDTH;

    objcounter = 0;

    SDL_BlitSurface(mapEl[0].get(), NULL, buf.get(), NULL);

    //DRAW FIELD
    for (j=0;j<height;j++) {
        for (i=0; i<width; i++) {

            pos.x=i*TILE_SIZE;
            pos.y=j*TILE_SIZE;
            pos.h=20;
            pos.w=20;

            if (walls[j*width+i]==1	&&	// horizontal line
                ( walls[j*width+i+1] != 0 || i == width-1 ) &&
                ( walls[j*width+i-1] != 0 || i == 0 ) ) {
                SDL_SetAlpha(mapEl[1].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(mapEl[1].get(), NULL, buf.get(), &pos );
            }

            else if (walls[j*width+i]==1)	{	// vertical line
                SDL_SetAlpha(mapElRot[1][0].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(mapElRot[1][0].get(), NULL, buf.get(), &pos);
            }

            else if (walls[j*width+i]==2 &&		//ghost door
                     walls[j*width+i + 1] != 0 &&
                     walls[j*width+i - 1] != 0) {
                SDL_SetAlpha(mapEl[2].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(mapEl[2].get(), NULL, buf.get(), &pos);
            }
            else if (walls[j*width+i]==2)	{	// vertical ghost door
                SDL_SetAlpha(mapElRot[2][0].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(mapElRot[2][0].get(), NULL, buf.get(), &pos);
            }

            else if (walls[j*width+i]==3) {		//upper left corner
                SDL_SetAlpha(mapEl[3].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(mapEl[3].get(), NULL, buf.get(), &pos);
            }
            else if (walls[j*width+i]==4) {		// upper right corner
                SDL_SetAlpha(mapEl[4].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(mapEl[4].get(), NULL, buf.get(), &pos);
            }
            else if (walls[j*width+i]==5) {		// lower  right corner
                SDL_SetAlpha(mapEl[5].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(mapEl[5].get(), NULL, buf.get(), &pos);
            }
            else if (walls[j*width+i]==6) {		// lower left corner
                SDL_SetAlpha(mapEl[6].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(mapEl[6].get(), NULL, buf.get(), &pos);
            }

            else if (walls[j*width+i]==7 && 		// left T
                     ( walls[j*width+i-1]==0 || i == 0 ) ) {
                SDL_SetAlpha(mapEl[7].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(mapEl[7].get(), NULL, buf.get(), &pos);
            }
            else if (walls[j*width+i]==7)	{	// upside down T
                SDL_SetAlpha(mapElRot[7][0].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(mapElRot[7][0].get(), NULL, buf.get(), &pos);
            }
            else if (walls[j*width+i]==8 &&		// right T
                     ( walls[j*width+i+1]==0 || i == width-1 ) ) {
                SDL_SetAlpha(mapEl[8].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(mapEl[8].get(), NULL, buf.get(), &pos);
            }
            else if (walls[j*width+i]==8)	{	// upright T
                SDL_SetAlpha(mapElRot[8][0].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(mapElRot[8][0].get(), NULL, buf.get(), &pos);
            }

            else if (walls[j*width+i]==9 &&
                     walls[j*width+i-1] != 0 &&
                     walls[j*width+i-1] != 2 &&
                     i > 0 )	 {//right stub
                SDL_SetAlpha(mapEl[9].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(mapEl[9].get(), NULL, buf.get(), &pos);
            }
            else if (walls[j*width+i]==9 &&
                     walls[j*width+i+1] != 0 &&
                     walls[j*width+i+1] != 2 &&
                     i < width-1) {	// left stub
                SDL_SetAlpha(mapElRot[9][1].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(mapElRot[9][1].get(), NULL, buf.get(), &pos);
            }
            else if (walls[j*width+i]==9 &&
                     walls[(j+1)*width+i] != 0 &&
                     walls[(j+1)*width+i] != 2 &&
                     j < height -1) {	// upper stub
                SDL_SetAlpha(mapElRot[9][0].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(mapElRot[9][0].get(), NULL, buf.get(), &pos);
            }
            else if (walls[j*width+i]==9)	{// lower stub
                SDL_SetAlpha(mapElRot[9][2].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(mapElRot[9][2].get(), NULL, buf.get(), &pos);
            }
        }
    }

    //DRAW OBJECTS

    for (j=0;j<height;j++) {
        for (i=0; i<width; i++) {

            pos.x=i*TILE_SIZE; // +10 are needed for correct placement
            pos.y=j*TILE_SIZE;
            pos.h=20;
            pos.w=20;

            if (foods[j*width+i]==Food::DOT) {
                SDL_SetAlpha(objEl[1].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(objEl[1].get(), NULL, buf.get(), &pos);
                objcounter++;
            }
            else if (foods[j*width+i]==Food::ENERGIZER) {
                SDL_SetAlpha(objEl[2].get(),SDL_SRCALPHA|SDL_RLEACCEL,alpha);
                SDL_BlitSurface(objEl[2].get(), NULL, buf.get(), &pos);
                objcounter++;
            }
            /*else if (foods[j*width+i]==3 && specialspawned && !specialeaten) {	// fruit TODO
                SDL_SetAlpha(objEl[3].get(),SDL_SRCALPHA,fruitalpha);
                SDL_BlitSurface(objEl[3].get(), NULL, buf.get(), &pos);
                objcounter++;
            }*/
        }
    }


}

#define BACKGROUND_TEXTURE_ID 0

void BckgrObj::LoadTextures(std::string path) {

    int i;
    std::string num[NUMOFMAPTEX];
    SDL_PixelFormat *fmt;

    for (i=0;i<NUMOFMAPTEX;i++)
        num[i]='0'+i;

    for (i=0;i<NUMOFMAPTEX;i++) {
        mapEl[i].reset(IMG_Load((path + "m" + num[i] + ".png").c_str()), SDL_FreeSurface);
        if ( mapEl[i] == NULL )
            throw_exception(num[i] + "Failed to load map texture");

        //get pixel format from surface
        fmt=mapEl[i]->format;

        //set the transparent color key to RGB 255 0 255
        SDL_SetColorKey(mapEl[i].get(),SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(fmt,255,0,255));

        // scale to tile size
        if (i != BACKGROUND_TEXTURE_ID) {
            scale_to_size(mapEl[i], TILE_SIZE);
        }

        for (int j=0;j<3;j++) {
            mapElRot[i][j]=Rotate(mapEl[i],(j+1)*90);
        }
    }
    for (i=1;i<5;i++) {
        objEl[i].reset(IMG_Load((path + "o" + num[i] + ".png").c_str()), SDL_FreeSurface);
        if ( objEl[i] == NULL )
            throw_exception(num[i] + "Failed to load object texture");

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
    objcounter(0),
    fruitalpha(255),
    specialspawned(false),
    specialeaten(false)
{
}

    }
}
