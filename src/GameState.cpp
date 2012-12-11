/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/*
 * Pacman rules: 
 * TODO check our impl is valid, maybe even write tests for it
 *
 * - 10 points for each dot
 * - 50 points for each energizer (big dot)
 * - 244 dots
 * - 4 energizers
 * - ghosts made vulnerable by energizer for 6 seconds
 * - ghosts eaten: first 200 points, then 400, 800, 1600. Is reset back to 200 upon eating a new energizer.
 * - 2 fruits appear at directly beneath monster pen after 70 and 170 dots. At level 1 they are worth 100 points. They remain for 10sec
 * - monster pen leaving: red spawns outside the first time, pink leaves after 0 dots are eaten, blue leaves after 30 dots eaten, orange leaves after 90 dots total eaten. If no dots are eaten for 4 seconds, the next monster leaves the pen. (in level 3 all monsters leave immediately, always, might want to take that level as simplification)
 * - speeds: see the table. Speed is determined solely by the current tile and state of the player. 100% speed = 9.5 tiles per sec.
 * - pacman and ghosts are free to change direction any time. Ghosts and pacman take in a path as AI.
 * - tunnel: wrap when tile pos exits map bounds. Wrap with pixel accuracy.
 *
 * In our case we'll start with 1 life. Later we'll add more lifes, but first let's solve the simpler problem
 *
 * The above rules only apply to level 1, I'm assuming pacman won't make it through the first level.
 *
 * The game's logic plays at a fixed rate of 60 ticks per second. So the max render rate is 60 frames per second.
 *
 * For full details: http://home.comcast.net/~jpittman2/pacman/pacmandossier.html
 */

#include "GameState.h"
#include "Sounds.h"
#include "App.h"
#include "Directions.h"
#include "GameStateInfo.h"
#include <string.h>

#define GHOST_BLINKY 0
#define GHOST_PINKY 1
#define GHOST_INKY 2
#define GHOST_CLYDE 3

extern App app;

static const SDL_Point PACMAN_SPAWN(14 * TILE_SIZE, 23.5 * TILE_SIZE);
static const SDL_Point GHOST_SPAWN = SDL_Point(14, 14) * TILE_SIZE;

using std::max;

extern Directions DIRECTIONS;

inline int at(SDL_Point tile_pos) {
    return tile_pos.y * MAP_WIDTH + tile_pos.x ;
}

/**
 * Create new game
 */
GameState::GameState(const int* walls, GameStateInfo& info)
:   food_count(244),
    score(0),
    lives(1),
    fruit_spawned(false),
    fruit_ticks_left(-1),
    vulnerable_ticks_left(-1),
    idler_ticks_left(-1),
    pacman(PACMAN_SPAWN),
    foods {
        Food::NONE, Food::NONE,      Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE,      Food::NONE,
        Food::NONE, Food::DOT,       Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,       Food::NONE,
        Food::NONE, Food::DOT,       Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,       Food::NONE,
        Food::NONE, Food::ENERGIZER, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,       Food::NONE,
        Food::NONE, Food::DOT,       Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,       Food::NONE,
        Food::NONE, Food::DOT,       Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,       Food::NONE,
        Food::NONE, Food::DOT,       Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,       Food::NONE,
        Food::NONE, Food::DOT,       Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,       Food::NONE,
        Food::NONE, Food::DOT,       Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,       Food::NONE,
        Food::NONE, Food::NONE,      Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE,      Food::NONE,
        Food::NONE, Food::NONE,      Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE,      Food::NONE,
        Food::NONE, Food::NONE,      Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE,      Food::NONE,
        Food::NONE, Food::NONE,      Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE,      Food::NONE,
        Food::NONE, Food::NONE,      Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE,      Food::NONE,
        Food::NONE, Food::NONE,      Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE,      Food::NONE,
        Food::NONE, Food::NONE,      Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE,      Food::NONE,
        Food::NONE, Food::NONE,      Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE,      Food::NONE,
        Food::NONE, Food::NONE,      Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE,      Food::NONE,
        Food::NONE, Food::NONE,      Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE,      Food::NONE,
        Food::NONE, Food::NONE,      Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE,      Food::NONE,
        Food::NONE, Food::DOT,       Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,       Food::NONE,
        Food::NONE, Food::DOT,       Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,       Food::NONE,
        Food::NONE, Food::DOT,       Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,       Food::NONE,
        Food::NONE, Food::ENERGIZER, Food::DOT,  Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::DOT,  Food::ENERGIZER, Food::NONE,
        Food::NONE, Food::NONE,      Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE,      Food::NONE,
        Food::NONE, Food::NONE,      Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE,      Food::NONE,
        Food::NONE, Food::DOT,       Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,       Food::NONE,
        Food::NONE, Food::DOT,       Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,       Food::NONE,
        Food::NONE, Food::DOT,       Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::DOT,  Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::DOT,       Food::NONE,
        Food::NONE, Food::DOT,       Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,  Food::DOT,       Food::NONE,
        Food::NONE, Food::NONE,      Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE, Food::NONE,      Food::NONE
    }
{
    SDL_Point spawn = GHOST_SPAWN;
    ghosts[0] = GhostState(spawn);

    spawn.x += 2 * TILE_SIZE;
    ghosts[1] = GhostState(spawn);

    spawn = GHOST_SPAWN;
    spawn.x -= 2 * TILE_SIZE;
    ghosts[2] = GhostState(spawn);

    spawn = GHOST_SPAWN;
    spawn.y -= 2.5 * TILE_SIZE;
    ghosts[3] = GhostState(spawn);

    // TODO once debug is over, comment this check
    int food_count_ = 0;
    for (int y=0; y<MAP_HEIGHT; ++y) {
        for (int x=0; x<MAP_WIDTH; ++x) {
            int food_index = y*MAP_WIDTH + x;
            //this->foods[food_index] = foods[food_index] == 1;
            if (this->foods[food_index] != Food::NONE) {
                ++food_count_;
            }
        }
    }
    // TODO we seem to have only 3 energizers, that's not right...
    assert(food_count_ == food_count); // TODO might want asserts to throw exceptions and have them add some interesting output to display too

    set_legal_actions(walls, NULL, NULL, info);
}

/*
 * Create successor of state
 */
GameState::GameState(const int* walls, const int* actions, const GameState* state, GameStateInfo& info)
:   pacman(state->pacman)  // pacman has no default constructor, so it gets angry unless I use this one
{
    std::cout // TODO just some debug output, ... directly to cout
        << actions[0] << ", "
        << actions[1] << ", "
        << actions[2] << ", "
        << actions[3] << ", "
        << actions[4] << std::endl;

    static const int VULNERABLE_TICKS = 6 * TICK_RATE;  // the amount of ticks ghosts are vulnerable
    static const int FRUIT_TICKS = 10 * TICK_RATE;  // the amount of ticks fruit stays on the map after spawning
    static const int FULL_SPEED = 9.5 * TILE_SIZE / TICK_RATE;  // 100% speed expressed in px per tick.

    // Note: order of everything in this function is important TODO split in functions to provide better overview of ordering

    // First copy everything
    memcpy(this, state, sizeof(GameState));

    // Vulnerable timing
    if (vulnerable_ticks_left == VULNERABLE_TICKS) {
        // Ghosts become vulnerable in this tick
        for (auto& ghost : ghosts) {
            if (ghost.state == GhostState::NORMAL) {
                ghost.state = GhostState::VULNERABLE;
            }
        }
    }
    else if (vulnerable_ticks_left == 0) {
        // Ghosts no longer vulnerable, make it so
        for (auto& ghost : ghosts) {
            if (ghost.state == GhostState::VULNERABLE) {
                ghost.state = GhostState::NORMAL;
            }
        }

        app.getSnd()->stop(7);
    }
    vulnerable_ticks_left = max(vulnerable_ticks_left - 1, -1);  // Consume 1 tick of timer


    // Fruit spawning
    if (fruit_ticks_left == 0) {
        // aw, too late, despawn fruit
        fruit_spawned = false;
    }
    if (state->food_count == 70 || state->food_count == 170) {
        // spawn a fruit
        assert(!fruit_spawned);  // It is impossible for another fruit to spawn while a previous is still spawned (eating 100 dots should take long enough for this never to happen)
        fruit_spawned = true;
        fruit_ticks_left = FRUIT_TICKS;
    }
    fruit_ticks_left = max(fruit_ticks_left - 1, -1);

    // Move players
    {
        // TODO cornering
        double speed_modifier;

        // move pacman
        if (idler_ticks_left <= 0) {
            if (get_vulnerable_ghost_count() > 0) {
                speed_modifier = 0.9;
            }
            else {
                speed_modifier = 0.8;
            }

            pacman.move(actions[0], FULL_SPEED * speed_modifier);
        }
        idler_ticks_left = max(idler_ticks_left - 1, -1);

        // move ghosts
        for (int i=0; i<GHOST_COUNT; i++) {
            if (ghosts[i].is_in_tunnel()) {
                speed_modifier = 0.4;
            }
            else if (ghosts[i].state = GhostState::VULNERABLE) {
                speed_modifier = 0.5;
            }
            else if (is_elroy2(i)) {
                speed_modifier = 0.85;
            }
            else if (is_elroy1(i)) {
                speed_modifier = 0.8;
            }
            else {
                speed_modifier = 0.75;
            }
            ghosts[i].move(actions[1+i], FULL_SPEED * speed_modifier);
        }
    }


    ///////////////////////////////////////////
    // Handle collisions
    ///////////////////////////////////////////

    // Note: An action that leads to colliding with a wall is illegal, so we needn't check for that.
    // TODO what about movement rounding errors though, won't that push us into walls and such?

    auto pacman_tpos = pacman.get_tile_pos();
    for (auto& ghost : ghosts) {
        if (pacman_tpos == ghost.get_tile_pos()) {
            // collide with ghost
            if (ghost.state == GhostState::NORMAL) {
                // pacman gets eaten
                lives--;

                app.getSnd()->stop();
                app.getSnd()->play(8, 0);

                app.delay(1000);

                if (get_lives() > 0) {
                    resetLvl();
                }
                return;
            }
            else if (ghost.state == GhostState::VULNERABLE) {
                // pacman eats ghost
                score += (int) pow(2.0, GHOST_COUNT - get_vulnerable_ghost_count()) * 200;
                ghost.state = GhostState::DEAD;
                app.getSnd()->play(4,0);
            }
        }
    }

    // collide with food
    int food_index = at(pacman_tpos);
    if (foods[food_index] == Food::DOT) {
        // eat small dot
        foods[food_index] = Food::NONE;
        --food_count;
        score += 10;

        app.dot_eaten();

        assert(idler_ticks_left == -1);
        idler_ticks_left = 1;  // pacman can't move for 1 tick after eating a dot
    }
    else if (foods[food_index] == Food::ENERGIZER) {
        foods[food_index] = Food::NONE;
        --food_count;
        score += 50;

        app.getSnd()->play(3, 0);
        app.getSnd()->play(7, 1);

        vulnerable_ticks_left = VULNERABLE_TICKS;

        assert(idler_ticks_left == -1);
        idler_ticks_left = 3;  // pacman can't move for 3 ticks after eating a dot
    }
    /*else if (fruit_spawned && foods[food_index] == 3) { // TODO fix
        // eat fruit
        score += get_fruit_score();
        app.getSnd()->play(5, 0);
        fruit_spawned = false;
    }*/


    ///////////////////////////////////
    //	OTHER
    ///////////////////////////////////


    // Calculate next legal actions
    set_legal_actions(walls, actions, state, info);
}

void GameState::set_legal_actions(const int* walls, const int* actions, const GameState* state, GameStateInfo& info) {
    for (int i=0; i<PLAYER_COUNT; ++i) {
        SDL_Point tpos;
        SDL_Point previous_tpos;

        if (i == 0) {
            tpos = pacman.get_tile_pos();
            if (state)
                previous_tpos = state->pacman.get_tile_pos();
        }
        else {
            tpos = ghosts[i-1].get_tile_pos();
            if (state)
                previous_tpos = state->ghosts[i].get_tile_pos();
        }

        if (!state) {
            // set previous pos to an invalid pos
            previous_tpos = SDL_Point(-1, -1);
        }

        if (tpos == previous_tpos) {
            // Next action has to be the same as current action
            info.legal_actions[i][0] = actions[i];
            for (int j=1; j<ACTION_COUNT; ++j) {
                info.legal_actions[i][j] = -1;
            }
        }
        else {
            // Any nonobstructed path is fine
            for (int j=0; j<ACTION_COUNT; ++j) {
                auto new_tpos = tpos + DIRECTIONS[j];
                bool is_legal_tpos = walls[at(new_tpos)] == 0 || new_tpos.x < 0 || new_tpos.x == MAP_WIDTH;
                info.legal_actions[i][j] = is_legal_tpos ? j : -1;
            }
            // TODO order reverse direction as last (swap its value with that of the last)
        }
    }
}

GameStateInfo GameState::start_new_game(const int* walls) {
    GameStateInfo info;
    info.state.reset(new GameState(walls, info));
    info.legal_actions;
    return info;
}

GameStateInfo GameState::get_successor(const int* walls, const int* actions) {
    assert(!did_pacman_win());
    assert(!did_pacman_lose());

    GameStateInfo info;
    info.state.reset(new GameState(walls, actions, this, info));
    return info;
}

bool GameState::get_vulnerable_ghost_count() const {
    int count = 0;
    for (auto ghost : ghosts) {
        if (ghost.state == GhostState::VULNERABLE)
            count++;
    }
    return count;
}

bool GameState::is_elroy1(int ghost_index) const {
    // TODO clyde should have left the pen, otherwise elroy speeds are no go!
    return ghost_index == GHOST_BLINKY && food_count <= 20;
}

bool GameState::is_elroy2(int ghost_index) const {
    return ghost_index == GHOST_BLINKY && food_count <= 10;
}

void GameState::nextLvl() {
    assert(false); // didn't expect pacman to win vs perfect ghosts

    /*std::string tmpstr;
    level++;

    app.getSnd()->stop();
    app.getSnd()->play(9);

    vuln_duration -= vuln_duration/10;

    ((Ghost*)objects[ rand()%4 +2])->changeDifficulty( rand()%15, rand()%5 );
    ((Ghost*)objects[ rand()%4 +2])->changeDifficulty( rand()%10, rand()%3 );

    objects[PAC]->reset(pacstartx, pacstarty);
    objects[GHOST1]->reset(baddiestartx, baddiestarty);
    objects[GHOST2]->reset(baddiestartx+2, baddiestarty);
    objects[GHOST3]->reset(baddiestartx-2, baddiestarty);
    objects[GHOST4]->reset(baddiestartx, baddiestarty-2);

    tmpstr = lvlpath[lvlpathcurrent] + OBJFILE;
    if ( ! loadMap(tmpstr, objmap) )
        throw Error("Error loading objmap.txt during Game::nextLvl()");

    vulnflag= false;
    deadghostcount= 0;
    floatingscorecounter = 0;
    floatingscore = 0;
    specialspawned = false;
    ((BckgrObj*)objects[0])->setSpecialSpawned(false);
    specialeaten = false;
    ((BckgrObj*)objects[0])->setSpecialEaten(false);
    specialhasbeenspawned = false;
    time = oldtime = SDL_GetTicks();
    ghosttick = 0;
    ((Pacman*)objects[PAC])->setSpeedMult( 1);
    levelcleared = false;

    if (ispaused) pause();


    SDL_Delay(1000);


    render();
    specialspawntime = rand() % (((BckgrObj*)objects[0])->getObjCount() -20) + 10;

    emptyMsgPump();
    inputwaiting = false;
    gamestarted = false;
    */
}

void GameState::resetLvl() {	// vars and positions when pacman dies during level
    assert(false); // we're testing with lives==0 for now

    /*app.getSnd()->stop();

    SDL_Delay(1000);

    app.getSnd()->play(9);


    // setting vars
    vulnflag= false;
    deadghostcount= 0;
    floatingscorecounter= 0;
    floatingscore= 0;
    ghosttick = 0;
    ((Pacman*)objects[PAC])->setSpeedMult( 1);

    if (ispaused) pause();

    objects[PAC]->reset(pacstartx, pacstarty);
    objects[GHOST1]->reset(baddiestartx, baddiestarty);
    objects[GHOST2]->reset(baddiestartx+2, baddiestarty);
    objects[GHOST3]->reset(baddiestartx-2, baddiestarty);
    objects[GHOST4]->reset(baddiestartx, baddiestarty-2);

    render();

    emptyMsgPump();
    gamestarted= false;
    inputwaiting = false;*/
}


