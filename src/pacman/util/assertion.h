/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <boost/assert.hpp>

/*
 * Inspired by Another Mediocre Assertion Mechanism for C++
 */

/* Pre conditions
 *
 * We don't check for invariants in require, because we assume each
 * modification of object state is followed by at least one ensure. 
 * Concretely:
 * - call at least one ensure at the end of each non-const method
 * - no public variables; modify them only through methods
 */
#define REQUIRE(condition) ASSERTION::my_assert(condition, "Require " #condition)


#ifdef DISABLE_ASSERTION_POST_CONDITIONS

#define ENSURE(condition) ((void)0)
#define ENSURE_(condition) ((void)0)
#define INVARIANT(condition) ((void)0)
#define ASSERT(condition) ((void)0)

#else

// Post conditions
// Don't use these in selectors

// for use in a method:
#define ENSURE(condition) ASSERTION::ensure(this, condition, "Ensure " #condition)
// for use in global functions
#define ENSURE_(condition) ASSERTION::my_assert(condition, "Ensure " #condition)

// Invariant, use inside Assertable::invariants()
#define INVARIANT(condition) ASSERTION::my_assert(condition, "Invariant: " #condition)

// Anything else
#define ASSERT(condition) ASSERTION::my_assert(condition, "Assert " #condition)

#endif


#include <boost/exception/error_info.hpp>
#include <boost/exception/exception.hpp>

namespace ASSERTION {

    class Assertable {
    public:
        virtual void invariants() const {}
    };

    typedef boost::error_info<struct tag_assertion_message, const char*> assertion_message;

    class AssertionException : public boost::exception {
    public:
        AssertionException() {}
    };

    void ensure(const Assertable* assertable, bool condition, const char* message);

    void my_assert(bool condition, const char* message);

}

