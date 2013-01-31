/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Tests.h"
#include <pacman/test/MovementTest.h>
#include <pacman/model/GameState.h>
#include <pacman/util/assertion.h>
#include <pacman/util/Point.h>
#include <pacman/Constants.h>

using std::cout;
using std::endl;
using std::vector;
using std::string;

using namespace PACMAN::MODEL;
using namespace PACMAN::SPECIFICATION;

namespace PACMAN {
    namespace TEST {
        namespace MODEL {

/*
 * Map has 240 dots and 4 energizers
 */
void test_start_foods() {
    // validate a part of requirements: start_foods
    int dot_count = 0;
    int energizer_count = 0;
    for (int y=0; y<MAP_HEIGHT; ++y) {
        for (int x=0; x<MAP_WIDTH; ++x) {
            int food_index = y*MAP_WIDTH + x;
            if (start_foods[food_index] == Food::DOT) {
                ++dot_count;
            }
            if (start_foods[food_index] == Food::ENERGIZER) {
                ++energizer_count;
            }
        }
    }
    ASSERT(dot_count == 240);
    ASSERT(energizer_count == 4);
}

/*
 * Correct initial state
 */
void test_initial_game_state() {
    MovementTest test(PLAYER_PACMAN);
    auto state = test.get_state();

    // spawn positions
    ASSERT(state.get_player(PLAYER_PACMAN).get_pixel_pos() == FPoint(14, 23.5) * TILE_SIZE);
    ASSERT(state.get_player(PLAYER_PACMAN).get_tile_pos() == IPoint(14, 23));
    ASSERT(state.get_player(GHOST_BLINKY+1).get_pixel_pos() == FPoint(14, 11.5) * TILE_SIZE);
    ASSERT(state.get_player(GHOST_PINKY+1).get_pixel_pos() == FPoint(14, 14) * TILE_SIZE);
    ASSERT(state.get_player(GHOST_INKY+1).get_pixel_pos() == FPoint(12, 14) * TILE_SIZE);
    ASSERT(state.get_player(GHOST_CLYDE+1).get_pixel_pos() == FPoint(16, 14) * TILE_SIZE);

    // other
    ASSERT(state.get_lives() == 1);
    ASSERT(state.get_level() == 1);
}

/*
 * Regression test to an earlier fix
 */
void test_ghosts_remain_normal_when_not_eating_energizer() {
    MovementTest test(1);
    test.move(Direction::ANY);
}

/*
 * Correct timing normal speed pacman movement
 */
void test_pacman_movement_regular_speed_not_cornering() {
    MovementTest test(PLAYER_PACMAN);

    int one_tile_steps = ceil(1 /*tile*/ / (FULL_SPEED * NORMAL_PACMAN_SPEED));
    ASSERT(test.move(Direction::EAST) == one_tile_steps +1); // +1 because the first tick is a tick for the initial game state to tell players what to do, actual movement starts from the second tick onwards
    auto tile_pos = test.get_state().get_player(PLAYER_PACMAN).get_tile_pos();
    ASSERT(tile_pos == IPoint(15, 23));

    // check we are really moving east
    test.move(Direction::EAST);
    tile_pos = test.get_state().get_player(PLAYER_PACMAN).get_tile_pos();
    ASSERT(tile_pos == IPoint(16, 23));
}

/*
 * Correct timing of dot eating when not cornering
 */
void test_dot_eating_no_cornering() {
    MovementTest test(PLAYER_PACMAN);

    int start_food = test.get_state().get_food_count();
    int steps = test.move(Direction::EAST);
    ASSERT(test.get_state().get_food_count() == start_food - 1);

    // should take 1 step longer because pacman idles 1 tick after eating a dot
    int one_tile_steps = ceil(1 /*tile*/ / (FULL_SPEED * NORMAL_PACMAN_SPEED));
    ASSERT(test.move(Direction::EAST) == 1 + one_tile_steps + steps);
    ASSERT(test.get_state().get_food_count() == start_food - 2);
}

/*
 * Correct cornering
 */
void test_pacman_movement_regular_speed_cornering() {
    MovementTest test(PLAYER_PACMAN);
    int start_food = test.get_state().get_food_count();

    // move from spawn to corner point and then into the wall
    auto steps = test.move(Direction::NORTH);
    ASSERT(steps == 8 
            +1); // new game step
    auto tile_pos = test.get_state().get_player(PLAYER_PACMAN).get_tile_pos();
    ASSERT(tile_pos == IPoint(15, 23));
    ASSERT(test.get_state().get_food_count() == start_food - 1);

    // exit the wall
    steps = test.move(Direction::ANY);
    ASSERT(steps == 11 
            + 1 // dot idling
            + 1); // new game step
    tile_pos = test.get_state().get_player(PLAYER_PACMAN).get_tile_pos();
    ASSERT(tile_pos == IPoint(15, 22));
    ASSERT(test.get_state().get_food_count() == start_food - 2);

    // move to destination corner point, and exit into next tile
    steps = test.move(Direction::NORTH);
    ASSERT(steps == 18
            + 2 // dot idling
            + 1); // new game step
    tile_pos = test.get_state().get_player(PLAYER_PACMAN).get_tile_pos();
    ASSERT(tile_pos == IPoint(15, 21));
    ASSERT(test.get_state().get_food_count() == start_food - 3);
}

/* TODO
 * move from node to node takes expected amount of ticks:
 * - pacman:
 *   - at vulnerable speed: move between nodes (no cornering)
 * - ghost:
 *   - for every speed: move between 2 nodes
 */

}}}
