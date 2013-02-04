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

#include "DirectionInput.h"
#include "DirectionPreference.h"
#include <pacman/Constants.h>
#include <pacman/model/IntermediateGameState.h>

using std::cout;
using std::endl;
using std::vector;
using namespace ::PACMAN::MODEL;

namespace PACMAN {
    namespace RUN {

DirectionInput::DirectionInput(DirectionPreference& preference)
:   preference(preference)
{
}

bool DirectionInput::has_more() {
    return true;
}

Action DirectionInput::get_action(int player_index, const IntermediateGameState& state) {
    REQUIRE(state.get_action_count(player_index) > 0u);
    return state.get_action_along_direction(player_index, preference.get_preferred_direction());
}

}}
