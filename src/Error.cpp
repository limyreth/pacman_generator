/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Error.h"

Error::Error(std::string str) 
:   desc(str.c_str())
{
}

Error::Error(const char* str)
:   desc(str)
{
}
