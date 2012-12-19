/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "UIHints.h"

#include <SDL/SDL.h>
#include "Sounds.h"

UIHints::UIHints(Sounds* snd)
:   snd(snd)
{
}

void UIHints::delay(unsigned int ms) {
    //return; // TODO use bool no_gui or inheritance or something to switch whether or not to delay. Should only delay when showing things in GUI
    SDL_Delay(10*ms);  // 10* for easier debugging TODO rm again
}

void UIHints::ate_dot() {
    static unsigned int sound_counter = 0;
    snd->play(1 + sound_counter%2, 0, -500);
    sound_counter++;
}

void UIHints::ghosts_no_longer_vulnerable() {
    snd->stop(7);
}

void UIHints::ate_pacman() {
    snd->stop();
    snd->play(8, 0);
    delay(1000);
}

void UIHints::ate_ghost() {
    snd->play(4,0);
}

void UIHints::ate_energizer() {
    snd->play(3, 0);
    snd->play(7, 1);
}
