/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "Object.h"

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class SDL_Surface;

#define NUMPACANIM 8

namespace PACMAN {
    namespace MODEL {
        class PacmanState;
    }

    namespace GUI {

        // renderer/view of the pacman model/state
        class Pacman :
                public Object  // render object
        {
        public:
            Pacman(shared_ptr <SDL_Surface> buf, int os);

            void Draw(MODEL::PacmanState state);
            void Draw(int ix, int iy, int obj=3, int type=1);
            void LoadTextures(std::string path);
            void reset();

        private:
            unsigned int
                    animcounter;

            shared_ptr<SDL_Surface>
                    pacEl[NUMPACANIM],
                    pacElRot[NUMPACANIM][3];
        };

    }
}
