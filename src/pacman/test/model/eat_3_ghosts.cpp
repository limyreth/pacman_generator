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

void test_eat_3_ghosts() {
    const int steps = 746;

    const int pacman_origin = 258;
    const int pacman_destination = 370;
    const FPoint pacman_pos(156, 313.93420022523332591);

    const int blinky_origin = 3;
    const int blinky_destination = 1;
    const FPoint blinky_pos(336, 319.77999999999923375);
    const GhostState::State blinky_state = (GhostState::State)0;
    const bool blinky_vulnerable = 0;

    const int pinky_origin = 640;
    const int pinky_destination = 472;
    const FPoint pinky_pos(300, 214.64999999999903935);
    const GhostState::State pinky_state = (GhostState::State)0;
    const bool pinky_vulnerable = 0;

    const int inky_origin = 802;
    const int inky_destination = 634;
    const FPoint inky_pos(228, 309.83999999999832653);
    const GhostState::State inky_state = (GhostState::State)2;
    const bool inky_vulnerable = 0;

    const int clyde_origin = 7;
    const int clyde_destination = 3;
    const FPoint clyde_pos(384, 336);
    const GhostState::State clyde_state = (GhostState::State)3;
    const bool clyde_vulnerable = 1;

    ExternalGameState game_state;
    game_state.score = 1940;
    game_state.lives = 1;
    game_state.is_fruit_spawned = 0;
    game_state.is_game_over = 0;

    game_state.foods = Foods {{(Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)2, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)2, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)2, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)1, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0, (Food::Type)0}};

    /////////////////////////////////////////////////////////////////////////////////////////

    game_state.pacman = PacmanState(pacman_origin, pacman_destination, pacman_pos);
    game_state.ghosts = Ghosts {{
        GhostState(blinky_origin, blinky_destination, blinky_pos, blinky_state, blinky_vulnerable),
        GhostState(pinky_origin, pinky_destination, pinky_pos, pinky_state, pinky_vulnerable),
        GhostState(inky_origin, inky_destination, inky_pos, inky_state, inky_vulnerable),
        GhostState(clyde_origin, clyde_destination, clyde_pos, clyde_state, clyde_vulnerable)
    }};

    std::vector<Action> path = {0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};

    playback_test(path, game_state, PLAYER_PACMAN, steps);
}

}}}
