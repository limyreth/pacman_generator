/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

namespace PACMAN {

    namespace MODEL {

        class UIHints
        {
        public:
            virtual void ate_dot() = 0;
            virtual void ate_energizer() = 0;
            virtual void ate_ghost() = 0;
            virtual void ate_pacman() = 0;
            virtual void ate_fruit() = 0;
            virtual void ghosts_no_longer_vulnerable() = 0;
        };

    }
}
