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

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class SDL_Surface;

namespace PACMAN {
    namespace GUI {

        class BckgrObj :
                public Object
        {
        public:
            BckgrObj(shared_ptr<SDL_Surface> buffer, int os);

            void Draw(const SPECIFICATION::Foods foods);
            void Draw(int ix, int iy, int obj=3, int type=1);
            void Draw(int ix, int iy, int obj, int type, int alp);

            virtual void reset( int ix, int iy) { ix = iy; };   /* avoid compiler warnings */
            virtual void Update(int time) { time = 0; };        /* avoid compiler warnings */

            void LoadTextures(std::string path);

        private:
            shared_ptr<SDL_Surface>
                    map,
                    objEl[3];
        };

    }
}
