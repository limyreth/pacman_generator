/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include <pacman/util/Point.h>
#include <pacman/model/GhostState.h>
#include <pacman/model/PacmanState.h>
#include <pacman/model/GameState.h>
#include <pacman/specification/Food.h>
#include <pacman/test/playback_test.h>

#include <vector>

using ::PACMAN::MODEL::GhostState;
using ::PACMAN::MODEL::Ghosts;
using ::PACMAN::MODEL::PacmanState;
using ::PACMAN::MODEL::ExternalGameState;
using ::PACMAN::MODEL::Action;
using namespace ::PACMAN::SPECIFICATION;

namespace PACMAN {
    namespace TEST {
        namespace MODEL {

void test_eat_2_dots() {
    const int steps = 17;

    const int pacman_origin = 658;
    const int pacman_destination = 631;
    const FPoint pacman_pos(367.50035205760417512, 537.29964794239583625);

    const int blinky_origin = 640;
    const int blinky_destination = 472;
    const FPoint blinky_pos(300, 266.3999999999996362);
    const GhostState::State blinky_state = (GhostState::State)0;
    const bool blinky_vulnerable = false;

    const int pinky_origin = 3;
    const int pinky_destination = 1;
    const FPoint pinky_pos(336, 290.3999999999996362);
    const GhostState::State pinky_state = (GhostState::State)0;
    const bool pinky_vulnerable = false;

    const int inky_origin = 5;
    const int inky_destination = 3;
    const FPoint inky_pos(288, 336);
    const GhostState::State inky_state = (GhostState::State)3;
    const bool inky_vulnerable = false;

    const int clyde_origin = 7;
    const int clyde_destination = 3;
    const FPoint clyde_pos(384, 336);
    const GhostState::State clyde_state = (GhostState::State)3;
    const bool clyde_vulnerable = false;

    ExternalGameState game_state;
    game_state.score = 20;
    game_state.lives = 1;
    game_state.is_fruit_spawned = false;
    game_state.is_game_over = false;

    game_state.foods = Foods {{(Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)2, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)2, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)2, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)2, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0}};

    /////////////////////////////////////////////////////////////////////////////////////////

    game_state.pacman = PacmanState(pacman_origin, pacman_destination, pacman_pos);
    game_state.ghosts = Ghosts {{
        GhostState(blinky_origin, blinky_destination, blinky_pos, blinky_state, blinky_vulnerable),
        GhostState(pinky_origin, pinky_destination, pinky_pos, pinky_state, pinky_vulnerable),
        GhostState(inky_origin, inky_destination, inky_pos, inky_state, inky_vulnerable),
        GhostState(clyde_origin, clyde_destination, clyde_pos, clyde_state, clyde_vulnerable)
    }};

    std::vector<Action> path = {0, 1};

    playback_test(path, game_state, PLAYER_PACMAN, steps);
}

}}}
