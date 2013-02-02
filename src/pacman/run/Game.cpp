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

#include "Game.h"
#include "RecordedInput.h"
#include <pacman/Constants.h>
#include <pacman/run/ZeroInput.h>
#include <pacman/run/PlaybackInput.h>
#include <pacman/run/GameObserver.h>

#include <limits>

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using namespace ::PACMAN::MODEL;

namespace PACMAN {
    namespace RUN {

Game::Game()
:   state(IntermediateGameState::new_game()),
    steps(0),
    initialised(false)
{
}

void Game::init(Inputs inputs, shared_ptr<GameStateObserver> state_observer) {
    REQUIRE(!initialised);
    REQUIRE(inputs.size() == PLAYER_COUNT);
    this->inputs = inputs;
    this->state_observer = state_observer;
    initialised = true;
}

/*
 * Starts running the game or continues a last run that was stopped
 *
 * quit_at_step: -1 to ignore step count
 */
void Game::run(GameObserver& observer, bool pause_at_end_of_input, int stop_at_step) {
    REQUIRE(initialised);

    bool stop_at_end_of_input = !pause_at_end_of_input;
    while (!observer.should_stop() && stop_at_step != get_steps()) {
        if (!observer.is_paused()) {
            auto input = get_input();

            if (input.empty()) {
                if (stop_at_end_of_input) {
                    break;
                }
                else {
                    stop_at_end_of_input = true;
                    observer.pause();
                }
            }
            else {
                if (act(input)) {
                    observer.finished_step(get_state());
                }
            }
        }
    }
}

/*
 * Get player input for next game state
 *
 * Returns actions, or empty vector if we ran out of input
 */
vector<Action> Game::get_input() {
    REQUIRE(initialised);

    vector<Action> actions;
    actions.reserve(PLAYER_COUNT);

    for (int player_index = 0; player_index < PLAYER_COUNT; ++player_index) {
        if (state.get_action_count(player_index) > 0) {
            auto& input = inputs.at(player_index);
            if (input->has_more()) {
                actions.push_back(input->get_action(player_index, state));
            } else {
                actions.clear();
                break;
            }
        }
        else {
            actions.push_back(-1);
        }
    }

    return actions;
}

/*
 * Returns true when get_state() changed
 */
bool Game::act(const vector<Action>& actions) {
    REQUIRE(initialised);
    auto old_state = get_state();

    state = state.act(actions, *state_observer);

    if (old_state != get_state()) {
        steps++;
        return true;
    }
    else {
        return false;
    }
}

const MODEL::GameState& Game::get_state() {
    return state.get_predecessor();
}

/*
 * Print source code for test that replays this game,
 * and asserts reaching the same end game state
 */
void Game::print_recorded_test(std::ostream& out, RecordedInput& recorded_input) {
    out.precision(20);  // print with larger than max precision

    out << "/***************************************************************************" << endl
        << " *                                                                         *" << endl
        << " *   This program is free software; you can redistribute it and/or modify  *" << endl
        << " *   it under the terms of the GNU General Public License as published by  *" << endl
        << " *   the Free Software Foundation; either version 2 of the License, or     *" << endl
        << " *   (at your option) any later version.                                   *" << endl
        << " *                                                                         *" << endl
        << " ***************************************************************************/" << endl
        << endl
        << endl
        << "#include <pacman/util/Point.h>" << endl
        << "#include <pacman/model/GhostState.h>" << endl
        << "#include <pacman/model/PacmanState.h>" << endl
        << "#include <pacman/model/GameState.h>" << endl
        << "#include <pacman/specification/Food.h>" << endl
        << "#include <pacman/test/playback_test.h>" << endl
        << "" << endl
        << "#include <vector>" << endl
        << "" << endl
        << "using ::PACMAN::MODEL::GhostState;" << endl
        << "using ::PACMAN::MODEL::Ghosts;" << endl
        << "using ::PACMAN::MODEL::PacmanState;" << endl
        << "using ::PACMAN::MODEL::ExternalGameState;" << endl
        << "using ::PACMAN::MODEL::Action;" << endl
        << "using ::PACMAN::MODEL::PLAYER_PACMAN;" << endl
        << "using namespace ::PACMAN::SPECIFICATION;" << endl
        << "" << endl
        << "namespace PACMAN {" << endl
        << "    namespace TEST {" << endl
        << endl
        << "void test() {" << endl
        << "    const int steps = " << steps << ";" << endl
        << endl;

    get_state().print(out, "    ");

    out << endl
        << "    std::vector<Action> path = ";
    recorded_input.print_path(out);
    out << endl
        << "    playback_test(path, game_state, PLAYER_PACMAN, steps);" << endl
        << "}" << endl
        << endl
        << "}}";
}

int Game::get_steps() {
    return steps;
}

Inputs Game::make_inputs(int player_index, shared_ptr<Input> input) {
    shared_ptr<Input> zero_input(new ZeroInput);
    Inputs inputs(PLAYER_COUNT, zero_input);
    inputs.at(player_index) = input;
    return inputs;
}

Inputs Game::make_inputs(const vector<vector<Action>>& paths) {
    REQUIRE(paths.size() == PLAYER_COUNT);

    Inputs inputs;
    for (int player_index = 0; player_index < PLAYER_COUNT; ++player_index) {
        const auto& path = paths.at(player_index);
        if (!path.empty()) {
            inputs.push_back(shared_ptr<Input>(new PlaybackInput(path)));
        }
        else {
            inputs.push_back(shared_ptr<Input>(new ZeroInput));
        }
    }
    
    return inputs;
}

}}
