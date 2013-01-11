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
 */
#define REQUIRE(condition) ASSERTION::my_assert(condition, "Require " #condition)


#ifdef DISABLE_ASSERTION_POST_CONDITIONS

#define ENSURE(condition) ((void)0)
#define ASSERT_INVARIANTS() ((void)0)
#define INVARIANT(condition) ((void)0)
#define INVARIANTS_ON_EXIT 0
#define ASSERT(condition) ((void)0)

#else

// Post conditions
// Don't use these in selectors
#define ENSURE(condition) ASSERTION::my_assert(condition, "Ensure " #condition)

/* Call to check invariants
 *
 * You probably want INVARIANTS_ON_EXIT instead
 *
 * Recommend calling at end of each non-const method. I.e. whenever state
 * changes.
 *
 * Beware of:
 *
 * - public variables as they allow changing state without checking invariants
 *
 * - infinite recursion, e.g. invariants() calling a function that checks
 *   invariants at the end too.
 *
 * - return statements skipping your ENSUREs -> use http://www.boost.org/doc/libs/1_41_0/libs/scope_exit/doc/html/scope_exit/tutorial.html
 *
 * - return statements skipping your ASSERT_INVARIANTS -> Use INVARIANTS_ON_EXIT for that.
 */
#define ASSERT_INVARIANTS() this->invariants()

#define INVARIANTS_ON_EXIT ASSERTION::InvariantsOnExit _ASSERTION_invariants_on_exit(this)

// Invariant, use inside Assertable::invariants()
#define INVARIANT(condition) ASSERTION::my_assert(condition, "Invariant: " #condition)

// Anything else
#define ASSERT(condition) ASSERTION::my_assert(condition, "Assert " #condition)

#endif


#include <boost/exception/error_info.hpp>
#include <boost/exception/exception.hpp>

namespace ASSERTION {

    typedef boost::error_info<struct tag_assertion_message, const char*> assertion_message;

    class AssertionException : public boost::exception {
    public:
        AssertionException() {}
    };

    class InvariantsOnExit;

    class Assertable {
    protected:
        virtual void invariants() const = 0;
        friend InvariantsOnExit;
    };

    class InvariantsOnExit {
    public:
        InvariantsOnExit(Assertable* a) : assertable(a) {}
        ~InvariantsOnExit() {
            assertable->invariants();
        }

    private:
        Assertable* assertable;
    };

    void my_assert(bool condition, const char* message);

}

