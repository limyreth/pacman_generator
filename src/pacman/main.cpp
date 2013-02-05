/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

//////////////////////////////////////////////////////
// Pacman version 4
// Started September 5, 2008
// using C++ & SDL
// ported to linux with attempt at crossplatform compatibility
//////////////////////////////////////////////////////

#include "GUIMain.h"
#include "generator/generate.h"
#include "util/Log.h"
#include "util/assertion.h"
#include "test/Tests.h"

#include <sstream>
#include <algorithm>
#include <list>

#include "Constants.h"

using namespace PACMAN;
using namespace MODEL;
using namespace SPECIFICATION;
using TEST::test;
using GENERATOR::GeneratorMain;

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;

std::shared_ptr<GeneratorMain> generator_main;

int main(int argc, char** argv) {
    std::string str="";
    GUIMainArgs gui_main_args;
    gui_main_args.paths.resize(5);
    gui_main_args.gui_args.show_pacman_nodes = false;
    gui_main_args.gui_args.show_ghost_nodes = false;
    gui_main_args.gui_args.show_food = true;
    gui_main_args.gui_args.show_respawn_paths = false;
    gui_main_args.gui_args.show_grid = false;
    gui_main_args.gui_args.game_speed = 1.0;
    gui_main_args.pause_at_end = false;
    gui_main_args.quit_at_step = -1;
    gui_main_args.player_index = PLAYER_PACMAN;

    try {
        for (int i = 1;i<argc;i++) {
            str=argv[i];
            if (str=="--help") {
                std::cout
                    << endl
                    << "GUI-mode (= default mode) arguments:" << endl
                    << endl
                    << "\t--help" << endl
                    << "\t\tShow this message" << endl
                    << endl
                    << "\t--show-pacman-nodes" << endl
                    << "\t\tShow pacman movement graph" << endl
                    << endl
                    << "\t--show-ghost-nodes" << endl
                    << "\t\tShow ghost movement graph" << endl
                    << endl
                    << "\t--show-respawn-paths" << endl
                    << "\t\tShow ghost respawn path finding graph" << endl
                    << endl
                    << "\t--show-grid" << endl
                    << "\t\tShow tile grid" << endl
                    << endl
                    << "\t--hide-food" << endl
                    << "\t\tDon't render dots and energizers" << endl
                    << endl
                    << "\t--game-speed GAME_SPEED" << endl
                    << "\t\tDouble value to set game speed to, defaults to 1.0" << endl
                    << endl
                    << "\t--path PLAYER {A, B, C, ..., Z}" << endl
                    << "\t\tUse list of actions as input for player PLAYER" << endl
                    << endl
                    << "\t--pause-at-end" << endl
                    << "\t\tWhen using --path, pause at end of playback" << endl
                    << endl
                    << "\t--quit-at-step STEPS" << endl
                    << "\t\tQuit as soon as step count == STEPS" << endl
                    << endl
                    << "\t--player INDEX" << endl
                    << "\t\tSpecify which player to play with" << endl
                    << endl
                    << endl
                    << "In-game:" << endl
                    << "\tESC / q" << endl
                    << "\t\tQuit" << endl
                    << endl
                    << "\tArrow keys" << endl
                    << "\t\tMove pacman" << endl
                    << endl
                    << "\tp" << endl
                    << "\t\tPause game" << endl
                    << endl;
                return 0;
            }
            // gui subsystem arguments
            else if (str == "--show-pacman-nodes") {
                gui_main_args.gui_args.show_pacman_nodes = true;
            }
            else if (str == "--show-ghost-nodes") {
                gui_main_args.gui_args.show_ghost_nodes = true;
            }
            else if (str == "--hide-food") {
                gui_main_args.gui_args.show_food = false;
            }
            else if (str == "--show-respawn-paths") {
                gui_main_args.gui_args.show_respawn_paths = true;
            }
            else if (str == "--show-grid") {
                gui_main_args.gui_args.show_grid = true;
            }
            else if (str == "--quit-at-step") {
                i++;
                if (i >= argc) {
                    std::cerr << "Missing argument for --quit-at-step" << endl;
                    return 1;
                }

                std::istringstream str(argv[i]);
                str >> gui_main_args.quit_at_step;
            }
            else if (str == "--player") {
                i++;
                if (i >= argc) {
                    std::cerr << "Missing argument for --player" << endl;
                    return 1;
                }

                std::istringstream str(argv[i]);
                str >> gui_main_args.player_index;
            }
            else if (str == "--pause-at-end") {
                gui_main_args.pause_at_end = true;
            }
            else if (str == "--game-speed") {
                i++;
                if (i >= argc) {
                    std::cerr << "Missing argument for --game-speed" << endl;
                    return 1;
                }

                std::istringstream str(argv[i]);
                str >> gui_main_args.gui_args.game_speed;
            }
            else if (str == "--path") {
                i++;
                if (i >= argc) {
                    std::cerr << "Missing argument for --path" << endl;
                    return 1;
                }

                unsigned int player_index;
                {
                    std::istringstream str(argv[i]);
                    str >> player_index;
                }

                i++;
                if (i >= argc) {
                    std::cerr << "Missing argument for --path" << endl;
                    return 1;
                }

                if (!gui_main_args.paths.at(player_index).empty()) {
                    std::cerr << "Multiple --path for same player" << endl;
                    return 1;
                }

                // make space separated sequence of actions
                string path_str(argv[i]);
                std::replace(path_str.begin(), path_str.end(), '{', ' ');
                std::replace(path_str.begin(), path_str.end(), ',', ' ');
                std::replace(path_str.begin(), path_str.end(), '}', ' ');

                // now turn it into a list of Action
                std::istringstream str(path_str);
                Action action;
                str >> action;
                while (!str.fail()) {
                    gui_main_args.paths.at(player_index).push_back(action);
                    str >> action;
                }
            }
            // test subsystem arguments
            else if (str == "--test") {
                i++;
                if (i >= argc) {
                    std::cerr << "Missing argument to --test" << endl;
                    return 1;
                }
                string name = argv[i];

                test(name);
                return 0;
            }
            // generator subsystem arguments
            else if (str == "--generate") {
                i++;
                if (i >= argc) {
                    std::cerr << "Missing argument to --generate" << endl;
                    return 1;
                }
                string saves_dir = argv[i];

                i++;
                if (i >= argc) {
                    std::cerr << "Missing argument to --generate" << endl;
                    return 1;
                }
                unsigned int max_choices;

                std::istringstream str(argv[i]);
                str >> max_choices;

                generator_main.reset(new GeneratorMain(saves_dir, max_choices));
                generator_main->run();
                return 0;
            }
            else {
                std::cerr << "unrecognized commandline option\n";
                return 1;
            }
        }

        GUIMain main;
        main.run(gui_main_args);
    }
    catch (...) {
        logtxt.log_exception(std::current_exception());
    }

    return 0;
}
