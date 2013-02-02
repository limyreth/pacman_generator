/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "GUIMain.h"
#include <pacman/run/Game.h>
#include <pacman/run/DirectionInput.h>
#include <pacman/run/PlaybackInput.h>
#include <pacman/run/RecordedInput.h>
#include <pacman/run/ZeroInput.h>
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

void GUIMain::run(const GUIMainArgs& args) {
    GUI::GUI gui(args.gui_args);

    Inputs inputs;
    for (int player_index = 0; player_index < PLAYER_COUNT; ++player_index) {
        const auto& path = args.paths.at(player_index);
        if (!path.empty()) {
            vector<Action> vpath(path.begin(), path.end());
            inputs.push_back(shared_ptr<Input>(new PlaybackInput(vpath)));
        }
        else {
            if (player_index == args.player_index) {
                inputs.push_back(shared_ptr<Input>(new DirectionInput(gui)));
            }
            else {
                inputs.push_back(shared_ptr<Input>(new ZeroInput));
            }
        }
    }
    shared_ptr<RecordedInput> recorded_input(new RecordedInput(inputs.at(args.player_index)));
    inputs.at(args.player_index) = recorded_input;

    Game game;
    game.init(inputs, gui.create_state_observer());

    BOOST_SCOPE_EXIT(&recorded_input) {
        recorded_input->print_path(cout);
    } BOOST_SCOPE_EXIT_END

    game.run(gui, args.pause_at_end, args.quit_at_step);

    std::ofstream out("generated_test.cpp", ios::out);
    game.print_recorded_test(out, *recorded_input); 
    out.close();
}

}
