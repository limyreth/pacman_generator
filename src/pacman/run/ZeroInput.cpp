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

#include "ZeroInput.h"
#include <pacman/model/IntermediateGameState.h>

using std::cout;
using std::endl;
using namespace ::PACMAN::MODEL;

namespace PACMAN {
    namespace RUN {

bool ZeroInput::has_more() {
    return true;
}

Action ZeroInput::get_action(int player_index, const IntermediateGameState& state) {
    return 0;
}

}}
