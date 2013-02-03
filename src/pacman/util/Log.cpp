/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Log.h"
#include "error.h"
#include "assertion.h"

#include <iostream>

Log logtxt;

Log::Log()
{
}

Log::~Log()
{
}

void Log::log_exception(const std::string str) {
    std::cerr << str << std::endl;
}

void Log::log_exception(const std::exception_ptr& ptr) {
    try {
        std::rethrow_exception(ptr);
    }
    catch (const ASSERTION::AssertionException& e) {
        log_exception(e);
    }
    catch (const std::exception& e) {
        log_exception(e);
    }
    exit(1);
}

void Log::log_exception(const ASSERTION::AssertionException& e) {
    auto* message = boost::get_error_info<ASSERTION::assertion_message>(e);

    std::ostringstream out;
    out << "Assertion failed: " << *message;

    log_exception(out.str());
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

    log_exception(out.str());
}

