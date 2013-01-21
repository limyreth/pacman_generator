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

#include "model/Game.h"
#include "generator/generate.h"
#include "gui/GUI.h"
#include "Log.h"
#include "util/assertion.h"
#include "tests/Tests.h"
#include <sstream>

#include "Constants.h"

using namespace PACMAN;
using namespace MODEL;
using TEST::test;

using std::string;
using std::cout;
using std::vector;

int main( int argc, char** argv ) {
    std::string str="";
    GUI::GUIArgs gui_args;
    gui_args.show_pacman_nodes = false;
    gui_args.show_ghost_nodes = false;
    gui_args.show_food = true;

    try {
        logtxt.setFilename(".pacman_sdl");

        for (int i = 1;i<argc;i++) {
            str=argv[i];
            if (str=="--help") {
                std::cout << "pacman usage:\n\ncommandline arguments\n--help:\t\tshow this message\n"
                        << "ingame\nesc/q:\tquit\narrows:\tmovement\n"
                        << "n:\tnew game\n"
                        << "f:\ttoggle fps display\n";
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
                GENERATOR::run_generate();
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
            else
                std::cerr << "unrecognized commandline option\n";
        }

        // interactive mode
        MODEL::Game game(0);
        GUI::GUI gui(game.get_state(), gui_args);
        shared_ptr<UIHints> uihints = gui.create_uihints();

        while (gui.emptyMsgPump()) {
            game.act(gui.get_preferred_direction(), *uihints);
            gui.render();
        }

        logtxt.print( "Shutdown" );
    }
    catch (const ASSERTION::AssertionException& e) {
        logtxt.log_exception(e);
        return 1;
    }
    catch (const std::exception& e) {
        logtxt.log_exception(e);
        return 1;
    }

    return 0;
}
