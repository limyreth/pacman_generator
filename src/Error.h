/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "Main.h"
#include <boost/exception/all.hpp>
#include <boost/throw_exception.hpp>
#include <stdexcept>

#define throw_exception(msg) BOOST_THROW_EXCEPTION(std::runtime_error(msg))
