/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <memory>

class SDL_Surface;

namespace PACMAN {
    namespace GUI {
        void scale_to_size(std::shared_ptr<SDL_Surface>& surface, double size);
        void scale_to_size(std::shared_ptr<SDL_Surface>& surface, double sizex, double sizey);
    }
}
