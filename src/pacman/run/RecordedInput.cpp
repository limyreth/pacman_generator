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

Action RecordedInput::get_action(int player_index, const IntermediateGameState& state) {
    //REQUIRE(state.get_action_count(player_index) > 0);
    Action action = input->get_action(player_index, state);
    path.push_back(action);
    return action;
}

void RecordedInput::print_path(std::ostream& out) {
    out << "{";
    if (!path.empty()) {
        auto it = path.begin();
        out << (int)*it;
        it++;
        for (; it != path.end(); it++) {
            out << ", " << (int)*it;
        }
    }
    out << "};" << endl;
}

}}
