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

#include "../generator/GeneratorRun.h"
#include "../generator/Generator.h"
#include "../generator/PacmanGameTree.h"
#include "../generator/ChoiceTree.h"

#include "../util/assertion.h"

#include <sstream>

using std::cout;
using std::endl;
using std::stringstream;

using namespace ::PACMAN::MODEL;

using ::PACMAN::GENERATOR::PacmanGameTree;
using ::PACMAN::GENERATOR::ChoiceTree;
using ::PACMAN::GENERATOR::Generator;
using ::PACMAN::GENERATOR::GeneratorRun;

namespace PACMAN {
    namespace TEST {

void GeneratorTests::test_1() {
    // run for small amount of rounds without crashing or looping infinitely
    const int max_rounds = 10;
    GENERATOR::PacmanGameTree game_tree(max_rounds);
    GENERATOR::ChoiceTree choice_tree(game_tree);
    GENERATOR::Generator generator(choice_tree);
    generator.start();
    generator.join();
}

void GeneratorTests::test_save_load() {
    // save load separate parts first

    {
        stringstream str;
        auto state = GameState::new_game();
        state.save(str);

        GameState loaded_state(str);
        ASSERT(loaded_state == state);
    }

    {
        stringstream str;
        PacmanGameTree tree(10);
        tree.save(str);

        PacmanGameTree loaded_tree(str);
        ASSERT(loaded_tree == tree);
    }

    {
        stringstream str;
        PacmanGameTree game_tree(10);
        ChoiceTree choice_tree(game_tree);
        choice_tree.save(str);

        ChoiceTree loaded_tree(str, game_tree);
        ASSERT(loaded_tree == choice_tree);
    }

    {
        stringstream str;
        PacmanGameTree game_tree(10);
        ChoiceTree choice_tree(game_tree);
        Generator generator(choice_tree);
        generator.save(str);

        Generator loaded_generator(str, choice_tree);
        ASSERT(loaded_generator == generator);
    }
}

void GeneratorTests::test_save_load_of_running_instance() {
    std::chrono::milliseconds duration(50);
    shared_ptr<GeneratorRun> run(new GeneratorRun);

    for (int i=0; i < 5; ++i) {
        cout << i << endl;
        run->start();

        if (i > 0) {
            std::this_thread::sleep_for(duration);
        }

        stringstream str;
        run->stop(str);

        shared_ptr<GeneratorRun> loaded_run(new GeneratorRun(str));
        ASSERT(*loaded_run == *run);
        run = loaded_run;
    }
}

}}
