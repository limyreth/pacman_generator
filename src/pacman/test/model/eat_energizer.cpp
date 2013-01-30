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
using ::PACMAN::MODEL::PLAYER_PACMAN;
using namespace ::PACMAN::SPECIFICATION;

namespace PACMAN {
    namespace TEST {
        namespace MODEL {

void test_eat_energizer() {
    const int steps = 145;

    const int pacman_origin = 642;
    const int pacman_destination = 669;
    const FPoint pacman_pos(622.56830938309485646, 550.26119780197700493);

    const int blinky_origin = 292;
    const int blinky_destination = 68;
    const FPoint blinky_pos(156, 47.499999999999779732);
    const GhostState::State blinky_state = (GhostState::State)1;

    const int pinky_origin = 292;
    const int pinky_destination = 68;
    const FPoint pinky_pos(156, 107.49999999999920419);
    const GhostState::State pinky_state = (GhostState::State)1;

    const int inky_origin = 5;
    const int inky_destination = 3;
    const FPoint inky_pos(288, 336);
    const GhostState::State inky_state = (GhostState::State)3;

    const int clyde_origin = 7;
    const int clyde_destination = 3;
    const FPoint clyde_pos(384, 336);
    const GhostState::State clyde_state = (GhostState::State)3;

    ExternalGameState game_state;
    game_state.score = 220;
    game_state.lives = 1;
    game_state.is_fruit_spawned = false;
    game_state.is_game_over = false;

    game_state.foods = Foods {(Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)2, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)2, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)2, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0};

    /////////////////////////////////////////////////////////////////////////////////////////

    game_state.pacman = PacmanState(pacman_origin, pacman_destination, pacman_pos);
    game_state.ghosts = Ghosts {
        GhostState(blinky_origin, blinky_destination, blinky_pos, blinky_state),
        GhostState(pinky_origin, pinky_destination, pinky_pos, pinky_state),
        GhostState(inky_origin, inky_destination, inky_pos, inky_state),
        GhostState(clyde_origin, clyde_destination, clyde_pos, clyde_state)
    };

    std::vector<Action> path = {0, 1, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0};

    playback_test(path, game_state, PLAYER_PACMAN, steps);
}

}}}
