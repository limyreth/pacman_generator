/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "SDLUtility.h"

#include <SDL/SDL.h>

void delay(unsigned int ms) {
    //return; // TODO use bool no_gui or inheritance or something to switch whether or not to delay. Should only delay when showing things in GUI
    SDL_Delay(10*ms);  // 10* for easier debugging TODO rm again
}

