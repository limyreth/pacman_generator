/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <iostream>

namespace PACMAN {
    namespace UTIL {

        template <class InputIterator>
        void print_path(std::ostream& out, InputIterator begin, InputIterator end) {
            out << "{";
            if (begin != end) {
                auto it = begin;
                out << (int)*it;
                it++;
                for (; it != end; it++) {
                    out << ", " << (int)*it;
                }
            }
            out << "}";
        }

    }
}
