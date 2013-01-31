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

#include "DefaultGameObserver.h"
#include <pacman/model/NullGameStateObserver.h>

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using namespace ::PACMAN::MODEL;

namespace PACMAN {
    namespace RUN {

DefaultGameObserver::DefaultGameObserver(int player_index, std::shared_ptr<Input> input)
{
    game.init(Game::make_inputs(player_index, input), shared_ptr<GameStateObserver>(new NullGameStateObserver));
}

void DefaultGameObserver::finished_step(const GameState& state) {
}

bool DefaultGameObserver::should_stop() {
    return false;
}

bool DefaultGameObserver::is_paused() {
    return false;
}

void DefaultGameObserver::pause() {
    REQUIRE(false);
}

}}
