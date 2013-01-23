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
#include "../model/IntermediateGameState.h"

#include "../util/assertion.h"

#include <thread>

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
    const int max_choices = 10;
    GENERATOR::PacmanGameTree game_tree;
    GENERATOR::ChoiceTree choice_tree(game_tree, max_choices);
    GENERATOR::Generator generator(choice_tree);
    generator.run();
}

void GeneratorTests::test_save_load() {
    // save load separate parts first

    {
        stringstream str;
        PacmanGameTree game_tree;
        ChoiceTree choice_tree(game_tree, 10);
        choice_tree.save(str);

        PacmanGameTree game_tree2;
        ChoiceTree loaded_tree(str, game_tree2);
        ASSERT(loaded_tree == choice_tree);
    }

    {
        stringstream str;
        PacmanGameTree game_tree;
        ChoiceTree choice_tree(game_tree, 10);
        Generator generator(choice_tree);
        generator.save(str);

        Generator loaded_generator(str, choice_tree);
        ASSERT(loaded_generator == generator);
    }
}

void GeneratorTests::test_save_load_of_running_instance() {
    SaveLoadRunningGeneratorTest test;
    test.test();
}

void SaveLoadRunningGeneratorTest::thread_callback() {
    run->join(str);
}

void SaveLoadRunningGeneratorTest::test() {
    std::chrono::milliseconds duration(50);
    run.reset(new GeneratorRun);

    for (int i=0; i < 5; ++i) {
        cout << i << endl;

        std::thread thread(&SaveLoadRunningGeneratorTest::thread_callback, this);

        if (i > 0) {
            std::this_thread::sleep_for(duration);
        }

        run->stop();
        thread.join();

        std::shared_ptr<GeneratorRun> loaded_run(new GeneratorRun(str));
        ASSERT(*loaded_run == *run);
        run = loaded_run;
    }
}

}}
