/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "../Constants.h"

#include <memory>

class SDL_Surface;

namespace PACMAN {
    namespace GUI {

        class Object
        {
        public:
            Object(std::shared_ptr<SDL_Surface> buffer, int os )
            :	buf(buffer),
                    offset(os),
                    paused(true)
            {
            }

            virtual ~Object() {}

            void setPaused(bool b) { paused = b; }

            virtual void Draw(int ix, int iy, int obj=3, int type=1)=0;
            virtual void LoadTextures(std::string path)=0;

            virtual std::shared_ptr<SDL_Surface> Rotate(std::shared_ptr<SDL_Surface> src, int angle, double zoomx=1, double zoomy=1);
        protected:
            std::shared_ptr<SDL_Surface>
                    buf;

            const int
                    offset;

            bool
                    paused;
        };

    }
}
