/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "Sounds.h"

namespace PACMAN {
    namespace GUI {

        class NullSounds : public Sounds
        {
        public:
            virtual void play(int i, bool looped=0, int volume=128) {}
            virtual void stop(int i) {}
            virtual void stop() {}
            virtual void toggleSounds() {}
        };

    }
}
