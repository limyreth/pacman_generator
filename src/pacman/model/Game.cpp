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
#include "../Constants.h"

using std::cout;
using std::endl;
using std::vector;

namespace PACMAN {
    namespace MODEL {

Game::Game(int player_index)
:   state(IntermediateGameState::new_game()),
    player_index(player_index),
    steps(0)
{
    REQUIRE(player_index >= 0);
    REQUIRE(player_index < PLAYER_COUNT);
}

/*
 * Returns true when get_state() changed
 */
bool Game::act(Direction::Type direction, UIHints& uihints) {
    vector<Action> actions(PLAYER_COUNT, 0);
    auto old_state = get_state();

    if (state.get_action_count(player_index) > 0) {
        actions.at(player_index) = state.get_action_along_direction(player_index, direction);
        path.push_back(actions.at(player_index));
    }

    state = state.act(actions, uihints);

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
void Game::print_recorded_test(std::ostream& out) {
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
        << "#include <pacman/tests/playback_test.h>" << endl
        << "" << endl
        << "#include <vector>" << endl
        << "" << endl
        << "using ::PACMAN::MODEL::GhostState;" << endl
        << "using ::PACMAN::MODEL::Ghosts;" << endl
        << "using ::PACMAN::MODEL::PacmanState;" << endl
        << "using ::PACMAN::MODEL::GameState;" << endl
        << "using ::PACMAN::MODEL::Action;" << endl
        << "using ::PACMAN::MODEL::PLAYER_PACMAN;" << endl
        << "using namespace ::PACMAN::SPECIFICATION;" << endl
        << "" << endl
        << "namespace PACMAN {" << endl
        << "    namespace TEST {" << endl
        << endl
        << "void test() {" << endl
        << "   const int steps = " << steps << ";" << endl
        << endl;

    get_state().print(out, "    ");

    out << endl
        << "    std::vector<Action> path = {";
    if (!path.empty()) {
        auto it = path.begin();
        out << (int)*it;
        it++;
        for (; it != path.end(); it++) {
            out << ", " << (int)*it;
        }
    }
    out << "};" << endl
        << endl
        << "    playback_test(path, game_state, PLAYER_PACMAN, steps);" << endl
        << "}" << endl
        << endl
        << "}}";
}

}}
