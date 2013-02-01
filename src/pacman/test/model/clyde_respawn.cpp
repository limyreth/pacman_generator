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

void test_clyde_respawn() {
    const int steps = 1403;

    const int pacman_origin = 162;
    const int pacman_destination = 165;
    const FPoint pacman_pos(601.48303191087325104, 132);

    const int blinky_origin = 282;
    const int blinky_destination = 450;
    const FPoint blinky_pos(36, 173.74999999999872102);
    const GhostState::State blinky_state = (GhostState::State)1;

    const int pinky_origin = 58;
    const int pinky_destination = 282;
    const FPoint pinky_pos(36, 113.74999999999933209);
    const GhostState::State pinky_state = (GhostState::State)1;

    const int inky_origin = 460;
    const int inky_destination = 292;
    const FPoint inky_pos(156, 133.89999999999872671);
    const GhostState::State inky_state = (GhostState::State)1;

    const int clyde_origin = 3;
    const int clyde_destination = 7;
    const FPoint clyde_pos(371.15000000000259206, 336);
    const GhostState::State clyde_state = (GhostState::State)2;

    ExternalGameState game_state;
    game_state.score = 1050;
    game_state.lives = 1;
    game_state.is_fruit_spawned = 1;
    game_state.is_game_over = 0;

    game_state.foods = Foods {(Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)2, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)2, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0};

    /////////////////////////////////////////////////////////////////////////////////////////

    game_state.pacman = PacmanState(pacman_origin, pacman_destination, pacman_pos);
    game_state.ghosts = Ghosts {
        GhostState(blinky_origin, blinky_destination, blinky_pos, blinky_state),
        GhostState(pinky_origin, pinky_destination, pinky_pos, pinky_state),
        GhostState(inky_origin, inky_destination, inky_pos, inky_state),
        GhostState(clyde_origin, clyde_destination, clyde_pos, clyde_state)
    };

    std::vector<Action> path = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 2, 0, 2, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 0};

    playback_test(path, game_state, PLAYER_PACMAN, steps);
}

}}}
