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

    template <typename T>
    void read(std::istream& in, const T& what) {
        in.read((char*)&what, sizeof(T));
    }

    template <typename T>
    void write(std::ostream& out, const T& what) {
        out.write((const char*)&what, sizeof(T));
    }

}
