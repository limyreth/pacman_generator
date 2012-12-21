/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

namespace PACMAN {
    namespace GUI {

        class Sounds
        {
        public:
            virtual ~Sounds() {};
            virtual void play(int i, bool looped=0, int volume=128) = 0;
            virtual void stop(int i) = 0;
            virtual void stop() = 0;
            virtual void toggleSounds() = 0;
        };

    }
}
