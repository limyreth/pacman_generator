/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "GeneratorTests.h"

#include "util.h"

#include "../generator/Generator.h"
#include "../generator/PacmanGameTree.h"
#include "../generator/ChoiceTree.h"

using std::cout;
using std::endl;

namespace PACMAN {
    namespace TEST {

void GeneratorTests::test_1() {
    // run for small amount of rounds without crashing or looping infinitely
    const int max_rounds = 10;
    GENERATOR::PacmanGameTree game_tree(max_rounds);
    GENERATOR::ChoiceTree choice_tree(max_rounds, game_tree);
    GENERATOR::Generator generator(choice_tree);
    int best_score;
    generator.run(best_score);
}

}}
