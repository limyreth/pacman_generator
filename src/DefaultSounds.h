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

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class Mix_Chunk;

#define NUMOFSOUNDS 13

namespace PACMAN {
    namespace GUI {

        class DefaultSounds : public Sounds
        {
        public:
            DefaultSounds();
            ~DefaultSounds();
            void play(int i, bool looped=0, int volume=128);
            void stop(int i);
            void stop();
            void toggleSounds();

        private:
            shared_ptr<Mix_Chunk> snd[NUMOFSOUNDS];

            std::string sndPaths[NUMOFSOUNDS];

            bool isinit;
            bool on;
        };

    }
}
