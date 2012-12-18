/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Tests.h"

typedef void (*Test)();

void test_1() {
}

void test_2() {
    throw 1;
}

void test(int index) {
    Test tests[] = {
        test_1,
        test_2
    };
    tests[index]();
}
