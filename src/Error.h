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
#include <exception>

class Error : public std::exception
{
public:
    Error(std::string str);
    Error(const char* str);

    virtual const char* what() const throw()
    { 
        return desc; 
    }

private:
    const char* desc;
};
