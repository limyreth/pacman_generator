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

#include "interactive.h"
#include "generator/generate.h"
#include "util/Log.h"
#include "util/assertion.h"
#include "tests/Tests.h"

#include <sstream>
#include <algorithm>
#include <list>

#include "Constants.h"

using namespace PACMAN;
using namespace MODEL;
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
    GUI::GUIArgs gui_args;
    gui_args.show_pacman_nodes = false;
    gui_args.show_ghost_nodes = false;
    gui_args.show_food = true;
    gui_args.show_respawn_paths = false;
    gui_args.game_speed = 1.0;
    std::list<Action> path;

    try {
        logtxt.setFilename(".pacman_sdl");

        for (int i = 1;i<argc;i++) {
            str=argv[i];
            if (str=="--help") {
                std::cout
                    << endl
                    << "Interactive-mode arguments:" << endl
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
                    << "\t--hide-food" << endl
                    << "\t\tDon't render dots and energizers" << endl
                    << endl
                    << "\t--game-speed GAME_SPEED" << endl
                    << "\t\tDouble value to set game speed to, defaults to 1.0" << endl
                    << endl
                    << "\t--path {A, B, C, ..., Z}" << endl
                    << "\t\tUse list of actions as input (instead of keyboard)" << endl
                    << endl
                    << endl
                    << "In-game:" << endl
                    << "\tESC / q" << endl
                    << "\t\tQuit" << endl
                    << endl
                    << "\tArrow keys" << endl
                    << "\t\tMove pacman" << endl
                    << endl;
                return 0;
            }
            else if (str == "--test") {
                std::istringstream str(argv[i+1]);
                int index;
                str >> index;
                test(index-1);
                return 0;
            }
            else if (str == "--generate") {
                if (!(i == 1 && argc == 3)) {
                    std::cerr << "Incorrect arguments to generate" << endl;
                    return 1;
                }

                generator_main.reset(new GeneratorMain(string(argv[2])));
                generator_main->run();
                return 0;
            }
            else if (str == "--show-pacman-nodes") {
                gui_args.show_pacman_nodes = true;
            }
            else if (str == "--show-ghost-nodes") {
                gui_args.show_ghost_nodes = true;
            }
            else if (str == "--hide-food") {
                gui_args.show_food = false;
            }
            else if (str == "--show-respawn-paths") {
                gui_args.show_respawn_paths = true;
            }
            else if (str == "--game-speed") {
                i++;
                if (i >= argc) {
                    std::cerr << "Missing argument for --game-speed" << endl;
                    return 1;
                }

                std::istringstream str(argv[i]);
                str >> gui_args.game_speed;
            }
            else if (str == "--path") {
                i++;
                if (i >= argc) {
                    std::cerr << "Missing argument for --path" << endl;
                    return 1;
                }

                // make space separated sequence of actions
                string path_str(argv[i]);
                std::replace(path_str.begin(), path_str.end(), '{', ' ');
                std::replace(path_str.begin(), path_str.end(), ',', ' ');
                std::replace(path_str.begin(), path_str.end(), '}', ' ');

                // now turn it into a list of Action
                std::istringstream str(path_str);
                int action;
                str >> action;
                while (!str.fail()) {
                    path.push_back(action);
                    str >> action;
                }

            }
            else {
                std::cerr << "unrecognized commandline option\n";
                return 1;
            }
        }

        InteractiveMain main;
        main.run(gui_args, path);

        logtxt.print( "Shutdown" );
    }
    catch (...) {
        logtxt.log_exception(std::current_exception());
    }

    return 0;
}
