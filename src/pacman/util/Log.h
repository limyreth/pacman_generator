/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <string>

namespace ASSERTION {
    class AssertionException;
}

class Log
{
public:
    Log();
    ~Log();

    void setFilename(std::string fn);
    void print(std::string txt);
    void log_exception(const std::string str);
    void log_exception(const ASSERTION::AssertionException& e);
    void log_exception(const std::exception& e);

private:
    std::string
            filename;
};

extern Log logtxt;
