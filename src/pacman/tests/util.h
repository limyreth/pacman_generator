/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "../Utility.h"

#include <sstream>
#include <boost/assert.hpp>

namespace PACMAN {
    namespace TEST {

#define assert_equals(actual_value, expected_value) BOOST_ASSERT_MSG(actual_value == expected_value, (to_string(actual_value) + " != " + to_string(expected_value)).c_str());

    }
}

