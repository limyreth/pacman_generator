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
    Game game;
    GUI::GUI gui(gui_args);

    auto inputs = Game::make_inputs(PLAYER_PACMAN, shared_ptr<Input>(new DirectionInput(gui)));
    shared_ptr<RecordedInput> recorded_input(new RecordedInput(inputs.at(PLAYER_PACMAN)));
    inputs.at(PLAYER_PACMAN) = recorded_input;
    game.init(inputs);

    shared_ptr<UIHints> uihints = gui.create_uihints();

    BOOST_SCOPE_EXIT(&recorded_input) {
        recorded_input->print_path(cout);
    } BOOST_SCOPE_EXIT_END

    while (gui.handle_events()) {
        if (!gui.is_paused()) {
            if (game.act(*uihints)) {
                gui.render(game.get_state());
            }
        }
    }

    std::ofstream out("generated_test.cpp", ios::out);
    game.print_recorded_test(out, *recorded_input); 
    out.close();
}

void InteractiveMain::playback(GUIArgs gui_args, const std::list<Action>& path, bool pause_at_end) {
    auto current_action = path.begin();
    IntermediateGameState state = IntermediateGameState::new_game();
    vector<Action> actions(PLAYER_COUNT, 0);

    GUI::GUI gui(gui_args);
    shared_ptr<UIHints> uihints = gui.create_uihints();

    bool quit_at_end = !pause_at_end;
    while (gui.handle_events()) {
        if (gui.is_paused()) {
            gui.render(state.get_predecessor());
        }
        else {
            if (state.get_action_count(PLAYER_PACMAN) > 0) {
                if (current_action == path.end()) {
                    if (quit_at_end) {
                        return;
                    }
                    else {
                        quit_at_end = true;
                        gui.pause();
                        continue;
                    }
                }
                actions.at(PLAYER_PACMAN) = *current_action;
                current_action++;
            }

            auto old_state = state.get_predecessor();
            state = state.act(actions, *uihints);

            if (old_state != state.get_predecessor()) {
                gui.render(state.get_predecessor());
            }
        }
    }
}

}
