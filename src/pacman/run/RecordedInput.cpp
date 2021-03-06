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

#include "RecordedInput.h"
#include <pacman/Constants.h>
#include <pacman/util/print.h>

using std::cout;
using std::endl;
using std::shared_ptr;
using namespace ::PACMAN::MODEL;

namespace PACMAN {
    namespace RUN {

RecordedInput::RecordedInput(shared_ptr<Input> input)
:   input(input)
{
}

bool RecordedInput::has_more() {
    return input->has_more();
}

Action RecordedInput::get_action(unsigned int player_index, const IntermediateGameState& state) {
    //REQUIRE(state.get_action_count(player_index) > 0u);
    Action action = input->get_action(player_index, state);
    path.push_back(action);
    return action;
}

void RecordedInput::print_path(std::ostream& out) {
    ::PACMAN::UTIL::print_path(out, path.begin(), path.end());
}


}}
