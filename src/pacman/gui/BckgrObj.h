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

// There are only 9, index 0 used to be background but is now no longer used
#define NUMOFMAPTEX 10

namespace PACMAN {
    namespace GUI {

        class BckgrObj :
                public Object
        {
        public:
            BckgrObj(shared_ptr<SDL_Surface> buffer, int os);

            void Draw(const int* walls, const SPECIFICATION::Foods foods);
            void Draw(int ix, int iy, int obj=3, int type=1);
            void Draw(int ix, int iy, int obj, int type, int alp);

            virtual void reset( int ix, int iy) { ix = iy; };   /* avoid compiler warnings */
            virtual void Update(int time) { time = 0; };        /* avoid compiler warnings */

            void LoadTextures(std::string path);

            void setSpecialSpawned(bool b) {specialspawned = b;	}
            void setSpecialEaten(bool b) {specialeaten = b;	}

            int getObjCount() {	return objcounter;	}

            void setFruitAlpha(int a);

        private:
            shared_ptr<SDL_Surface>
                    mapEl[NUMOFMAPTEX],
                    objEl[NUMOFMAPTEX],
                    mapElRot[NUMOFMAPTEX][3];

            int
                    objcounter,
                    fruitalpha;

            bool
                    specialspawned,
                    specialeaten;
        };

    }
}
