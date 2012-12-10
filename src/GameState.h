/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

#include "Main.h"
#include "PacmanState.h"
#include "GhostState.h"
#include "Directions.h"
#include "Food.h"

using boost::shared_ptr;

#define GHOST_COUNT 4
#define PLAYER_COUNT GHOST_COUNT + 1

class GameState;


#define ACTION_COUNT 4
struct GameStateInfo {
    shared_ptr<GameState> state;
    bool legal_actions[PLAYER_COUNT][ACTION_COUNT];  // legal_actions[player][action_index] player 0 is pacman, the next 4 are ghosts
};

class GameState : public boost::noncopyable  // why copy a big thing when you can point!
{
public:
    static GameStateInfo start_new_game(const int* walls);
    GameStateInfo get_successor(const int* walls, const int* actions);  // game state after 1 tick/frame

    bool get_vulnerable_ghost_count() const;

    inline int get_level() const {
        return 1;
    }

    inline int get_score() const {
        return score;
    }

    inline int get_lives() const {
        return lives;
    }

    inline bool did_pacman_lose() const {
        assert(lives >= 0);
        return lives == 0;
    }

    inline bool did_pacman_win() const {
        return food_count == 0;
    }

    inline PacmanState get_pacman_state() const {
        return pacman;
    }

    inline GhostState get_ghost_state(int ghost_index) const {
        return ghosts[ghost_index];
    }

    inline const Foods& get_foods() const {
        return foods;
    }

private:
    GameState(const int* walls);
    GameState(const int* walls, const int* actions, const GameState* state, GameStateInfo& info);

    void resetLvl();
    void nextLvl();

    inline int get_fruit_score() const {
        return 100;
    }

    bool is_elroy1(int ghost_index) const;
    bool is_elroy2(int ghost_index) const;

private:
    PacmanState pacman;
    GhostState ghosts[GHOST_COUNT];

    Foods foods; // shows where food lies on the map
    int food_count;
    int score;
    int lives;

    bool fruit_spawned;

    int vulnerable_ticks_left;  // how many more ticks ghosts will be vulnerable
    int fruit_ticks_left;  // amount of ticks left til fruit disappears
    int idler_ticks_left;  // ticks left til pacman gets off his lazy ass and starts moving again (pacman rests after eating dot or energizer)

    static const int VULNERABLE_TICKS = 6 * TICK_RATE;  // the amount of ticks ghosts are vulnerable
    static const int FRUIT_TICKS = 10 * TICK_RATE;  // the amount of ticks fruit stays on the map after spawning
    static const int FULL_SPEED = 9.5 * TILE_SIZE / TICK_RATE;  // 100% speed expressed in px per tick.

    static const SDL_Point PACMAN_SPAWN;
    static const SDL_Point GHOST_SPAWN;
};
