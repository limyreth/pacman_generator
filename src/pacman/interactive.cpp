/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "interactive.h"
#include <pacman/run/Game.h>
#include <pacman/run/DirectionInput.h>
#include <pacman/run/PlaybackInput.h>
#include <pacman/run/RecordedInput.h>
#include <pacman/Constants.h>

#include <fstream>
#include <boost/scope_exit.hpp>

using namespace ::PACMAN::RUN;
using namespace ::PACMAN::MODEL;
using ::PACMAN::GUI::GUIArgs;

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using std::ios;

namespace PACMAN {

void InteractiveMain::run(GUIArgs gui_args, std::list<Action> path, bool pause_at_end) {
    if (path.empty()) {
        run(gui_args);
    }
    else {
        playback(gui_args, path, pause_at_end);
    }
}

void InteractiveMain::run(GUIArgs gui_args) {
    GUI::GUI gui(gui_args);
    shared_ptr<UIHints> uihints = gui.create_uihints();

    Game game;
    shared_ptr<RecordedInput> recorded_input(new RecordedInput(shared_ptr<Input>(new DirectionInput(gui))));
    game.init(Game::make_inputs(PLAYER_PACMAN, recorded_input), uihints);

    BOOST_SCOPE_EXIT(&recorded_input) {
        recorded_input->print_path(cout);
    } BOOST_SCOPE_EXIT_END

    game.run(gui, false);

    std::ofstream out("generated_test.cpp", ios::out);
    game.print_recorded_test(out, *recorded_input); 
    out.close();
}

void InteractiveMain::playback(GUIArgs gui_args, const std::list<Action>& path, bool pause_at_end) {
    GUI::GUI gui(gui_args);

    Game game;
    vector<Action> vpath(path.begin(), path.end());
    game.init(Game::make_inputs(PLAYER_PACMAN, shared_ptr<Input>(new PlaybackInput(vpath))), gui.create_uihints());

    game.run(gui, pause_at_end);
}

}
