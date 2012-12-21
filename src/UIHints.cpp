/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "UIHints.h"
#include "SDLUtility.h"
#include "Sounds.h"

namespace PACMAN {
    namespace MODEL {

UIHints::UIHints(shared_ptr<GUI::Sounds> snd)
:   snd(snd)
{
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
    GUI::delay(1000);
}

void UIHints::ate_ghost() {
    snd->play(4,0);
}

void UIHints::ate_energizer() {
    snd->play(3, 0);
    snd->play(7, 1);
}

    }
}
