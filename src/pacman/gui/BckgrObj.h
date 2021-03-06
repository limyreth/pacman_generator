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
#include "../specification/Food.h"

#include <SDL/SDL.h>
#include <memory>

class SDL_Surface;

namespace PACMAN {
    namespace GUI {

        class BckgrObj :
                public Object
        {
        public:
            BckgrObj(std::shared_ptr<SDL_Surface> buffer, int os);

            void Draw(const SPECIFICATION::Foods foods, bool fruit_spawned, bool show_food);
            void Draw(int ix, int iy, int obj=3, int type=1);

            virtual void reset( int ix, int iy) { ix = iy; };   /* avoid compiler warnings */
            virtual void Update(int time) { time = 0; };        /* avoid compiler warnings */

            void LoadTextures(std::string path);

        private:
            std::shared_ptr<SDL_Surface>
                    map,
                    objEl[3];

            SDL_Rect fruit_pos;
        };

    }
}
