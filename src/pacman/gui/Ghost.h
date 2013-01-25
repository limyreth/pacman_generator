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

#include <memory>

class SDL_Surface;

namespace PACMAN {
    namespace MODEL {
        class GhostState;
    }

    namespace GUI {

        class Ghost :
                public Object
        {
        public:
            Ghost(std::shared_ptr<SDL_Surface> buf, int os, std::string fn);

            void Draw(const MODEL::GhostState& current);
            void Draw(int ix, int iy, int obj=0, int type=0) ;
            void LoadTextures(std::string path);
            void reset();

        private:
            int animcounter;

            std::shared_ptr<SDL_Surface>
                    ghostEl[4];

            std::string
                    filename;
        };

    }
}
