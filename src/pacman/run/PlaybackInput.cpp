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

#include "PlaybackInput.h"
#include <pacman/model/IntermediateGameState.h>
#include <pacman/Constants.h>

using std::cout;
using std::endl;
using std::vector;
using namespace ::PACMAN::MODEL;

namespace PACMAN {
    namespace RUN {

PlaybackInput::PlaybackInput(const vector<Action>& path)
:   path(path)
{
    current_action = this->path.begin();
}

bool PlaybackInput::has_more() {
    return current_action != path.end();
}

Action PlaybackInput::get_action(int player_index, const IntermediateGameState& state) {
    REQUIRE(state.get_action_count(player_index) > 0u);
    REQUIRE(has_more());
    auto action = *current_action;
    current_action++;
    return action;
}

}}
