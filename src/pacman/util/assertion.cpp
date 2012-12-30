/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "assertion.h"
#include <boost/exception/all.hpp>

namespace ASSERTION {

void my_assert(bool condition, const char* message) {
    if (!condition) {
        throw AssertionException() << assertion_message(message);
        // TODO add a message... 
        // TODO Add stack trace... Once we are running it regularly, rather than in a debugger, this will come in handy
    }
}

}
