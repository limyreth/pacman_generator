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

void test_eat_2_ghosts() {
    const int steps = 406;

    const int pacman_origin = 202;
    const int pacman_destination = 258;
    const FPoint pacman_pos(156, 232.42190539355644319);

    const int blinky_origin = 472;
    const int blinky_destination = 640;
    const FPoint blinky_pos(300, 223.19000000000028194);
    const GhostState::State blinky_state = (GhostState::State)2;
    const bool blinky_vulnerable = 0;

    const int pinky_origin = 472;
    const int pinky_destination = 640;
    const FPoint pinky_pos(300, 211.36999999999966349);
    const GhostState::State pinky_state = (GhostState::State)2;
    const bool pinky_vulnerable = 0;

    const int inky_origin = 1;
    const int inky_destination = 640;
    const FPoint inky_pos(316.7000000000015234, 276);
    const GhostState::State inky_state = (GhostState::State)0;
    const bool inky_vulnerable = 1;

    const int clyde_origin = 7;
    const int clyde_destination = 3;
    const FPoint clyde_pos(384, 336);
    const GhostState::State clyde_state = (GhostState::State)3;
    const bool clyde_vulnerable = 1;

    ExternalGameState game_state;
    game_state.score = 980;
    game_state.lives = 1;
    game_state.is_fruit_spawned = 0;
    game_state.is_game_over = 0;

    game_state.foods = Foods {(Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)2, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)2, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)2, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0};

    /////////////////////////////////////////////////////////////////////////////////////////

    game_state.pacman = PacmanState(pacman_origin, pacman_destination, pacman_pos);
    game_state.ghosts = Ghosts {
        GhostState(blinky_origin, blinky_destination, blinky_pos, blinky_state, clyde_vulnerable),
        GhostState(pinky_origin, pinky_destination, pinky_pos, pinky_state, clyde_vulnerable),
        GhostState(inky_origin, inky_destination, inky_pos, inky_state, clyde_vulnerable),
        GhostState(clyde_origin, clyde_destination, clyde_pos, clyde_state, clyde_vulnerable)
    };

    std::vector<Action> path = {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    playback_test(path, game_state, PLAYER_PACMAN, steps);
}

}}}
