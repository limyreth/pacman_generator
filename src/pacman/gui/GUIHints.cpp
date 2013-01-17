/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "GUIHints.h"
#include "SDLUtility.h"
#include "Sounds.h"

namespace PACMAN {
    namespace GUI {

GUIHints::GUIHints(shared_ptr<Sounds> snd)
:   snd(snd)
{
}

void GUIHints::ate_dot() {
    static unsigned int sound_counter = 0;
    snd->play(1 + sound_counter%2, 0, -500);
    sound_counter++;
}

void GUIHints::ghosts_no_longer_vulnerable() {
    snd->stop(7);
}

void GUIHints::ate_pacman() {
    snd->stop();
    snd->play(8, 0);
    delay(1000);
}

void GUIHints::ate_ghost() {
    snd->play(4,0);
}

void GUIHints::ate_energizer() {
    snd->play(3, 0);
    snd->play(7, 1);
}

void GUIHints::ate_fruit() {
    snd->play(5, 0);
}

}}
