/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Log.h"
#include "Error.h"
#include <fstream>

#define WNDTITLE	"pacman_sdl (" __DATE__ ", " __TIME__ ")"

void Log::print(std::string txt) {
    std::ofstream file(filename.c_str(), std::ios::app);

    if ( !file)
        throw_exception("Unable to open logfile");

    file << txt << std::endl;

    file.close();
}

void Log::setFilename(std::string fn) {
    filename = std::string(getenv("HOME")) + "/" + fn;

    std::ofstream file(filename.c_str());

    if ( !file)
        throw_exception("Unable to open logfile");

    file << WNDTITLE << std::endl;

    file.close();
}

Log::Log()
{
}

Log::~Log()
{
}

void Log::log_exception(const std::exception& e) {
    auto* file_name = boost::get_error_info<boost::throw_file>(e);
    auto* function_name = boost::get_error_info<boost::throw_function>(e);
    auto* line_number = boost::get_error_info<boost::throw_line>(e);

    std::ostringstream out;
    if (file_name) {
        // assume others are valid too iff file_name is valid
        out << *file_name <<  ":" << std::endl << *function_name << ":" << *line_number << ":" << std::endl;
    }
    out << e.what();

    std::cerr << out.str() << std::endl;
    print(out.str());
}

