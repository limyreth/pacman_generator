/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "PathTest.h"
#include <pacman/model/GameState.h>
#include <pacman/run/PlaybackInput.h>

#include <memory>

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;

using namespace ::PACMAN::MODEL;
using namespace ::PACMAN::RUN;

namespace PACMAN {
    namespace TEST {
        namespace MODEL {

PathTest::PathTest(std::vector<Action>& path)
:   DefaultGameObserver(PLAYER_PACMAN, shared_ptr<Input>(new PlaybackInput(path)))
{
}

GameState PathTest::run(int stop_at_step) {
    game.run(*this, false, stop_at_step);
    return game.get_state();
}

}}}
