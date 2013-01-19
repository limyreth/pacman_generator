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

#include "model/IntermediateGameState.h"
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
    bool show_pacman_nodes = false;
    bool show_ghost_nodes = false;
    bool show_food = true;

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
                show_pacman_nodes = true;
            }
            else if (str == "--show-ghost-nodes") {
                show_ghost_nodes = true;
            }
            else if (str == "--hide-food") {
                show_food = false;
            }
            else
                std::cerr << "unrecognized commandline option\n";
        }

        // interactive mode
        vector<Action> actions(PLAYER_COUNT, 0);
        MODEL::IntermediateGameState state = IntermediateGameState::new_game();
        GUI::GUI gui(state.get_predecessor(), show_pacman_nodes, show_ghost_nodes, show_food);
        shared_ptr<UIHints> uihints = gui.create_uihints();

        while (gui.emptyMsgPump()) {
            auto& pacman = state.get_player(0);
            if (pacman.get_legal_actions().count > 0) {
                actions.at(0) = pacman.get_action_along_direction(gui.get_preferred_direction());
            }
            auto successor = state.act(actions, *uihints);
            state = IntermediateGameState(successor, *uihints);

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
