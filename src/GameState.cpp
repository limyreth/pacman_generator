/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "GameState.h"
#include "Sounds.h"


#define SMALL_DOTS_SCORE 10
#define LARGE_DOTS_SCORE 50

#define GHOST_BLINKY 0
#define GHOST_PINKY 1
#define GHOST_INKY 2
#define GHOST_CLYDE 3

extern App app;

const SDL_Point GameState::PACMAN_SPAWN(13, 23);
const SDL_Point GameState::GHOST_SPAWN(13, 13);

using std::max;

/*
 * Pacman rules: 
 * TODO make this implementation consistent with it
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

extern Directions DIRECTIONS;

inline int at(SDL_Point tile_pos) {
    return tile_pos.y * MAP_WIDTH + tile_pos.x ;
}

/**
 * Create new game
 */
GameState::GameState(const int* walls, int* foods) 
:   food_count(244),
    score(0),
    lives(1),
    fruit_spawned(false),
    fruit_ticks_left(-1),
    vulnerable_ticks_left(-1),
    idler_ticks_left(-1),
    pacman(PACMAN_SPAWN)
{
    SDL_Point spawn = GHOST_SPAWN;
    ghosts[0] = GhostState(spawn);

    spawn.x += 2;
    ghosts[1] = GhostState(spawn);

    spawn = GHOST_SPAWN;
    spawn.x -= 2;
    ghosts[2] = GhostState(spawn);

    spawn = GHOST_SPAWN;
    spawn.y -= 2;
    ghosts[3] = GhostState(spawn);

    // TODO once debug is over, comment the food check (but only the check!!)
    this->foods = new bool[MAP_HEIGHT * MAP_WIDTH];
    int food_count_ = 0;
    for (int y=0; y<MAP_HEIGHT; ++y) {
        for (int x=0; x<MAP_WIDTH; ++x) {
            int food_index = y*MAP_WIDTH + x;
            this->foods[food_index] = foods[food_index] == 1;
            if (this->foods[food_index]) {
                ++food_count_;
            }
        }
    }
    assert(food_count_ == food_count);
}

/*
 * Create successor of state
 */
GameState::GameState(const int* walls, const int* actions, const GameState* state, GameStateInfo& info)
:   score(state->score),
    lives(state->lives),
    fruit_spawned(state->fruit_spawned),
    fruit_ticks_left(state->fruit_ticks_left),
    vulnerable_ticks_left(state->vulnerable_ticks_left),
    idler_ticks_left(state->idler_ticks_left),
    pacman(state->pacman)
{
    // Note: order of everything in this function is important TODO split in functions to provide better overview of ordering

    // Copy the rest too
    foods = new bool[MAP_HEIGHT * MAP_WIDTH]; // TODO rather not have this on heap, hardcode the map size and we can do this. Then pool gamestate objs
    for (int y=0; y<MAP_HEIGHT; ++y) {
        for (int x=0; x<MAP_WIDTH; ++x) {
            foods[y*MAP_WIDTH + x] = state->foods[y*MAP_WIDTH + x];
        }
    }

    for (int i=0; i < GHOST_COUNT; ++i) {
        ghosts[i] = state->ghosts[i];
    }

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
    if (foods[food_index] == 1) {
        // eat small dot
        foods[food_index] = 0;
        --food_count;
        score += SMALL_DOTS_SCORE;

        app.dot_eaten();

        assert(idler_ticks_left == -1);
        idler_ticks_left = 1;  // pacman can't move for 1 tick after eating a dot
    }
    else if ( foods[food_index] == 2 ) {
        // eat large dot
        foods[food_index] = 0;
        --food_count;
        score += LARGE_DOTS_SCORE;

        app.getSnd()->play(3, 0);
        app.getSnd()->play(7, 1);

        vulnerable_ticks_left = VULNERABLE_TICKS;

        assert(idler_ticks_left == -1);
        idler_ticks_left = 3;  // pacman can't move for 3 ticks after eating a dot
    }
    else if (fruit_spawned && foods[food_index] == 3) {
        // eat fruit
        score += get_fruit_score();
        app.getSnd()->play(5, 0);
        fruit_spawned = false;
    }


    ///////////////////////////////////
    //	OTHER
    ///////////////////////////////////


    // Calculate next legal actions
    for (int i=0; i<PLAYER_COUNT; ++i) {
        SDL_Point tpos;
        SDL_Point previous_tpos;

        if (i == 0) {
            tpos = pacman.get_tile_pos();
            previous_tpos = state->pacman.get_tile_pos();
        }
        else {
            tpos = ghosts[i-1].get_tile_pos();
            previous_tpos = state->ghosts[i].get_tile_pos();
        }

        if (tpos == previous_tpos) {
            // Next action has to be the same as current action
            for (int j=0; j<ACTION_COUNT; ++j) {
                info.legal_actions[i][j] = j == actions[i];
            }
        }
        else {
            // Any nonobstructed path is fine
            for (int j=0; j<ACTION_COUNT; ++j) {
                auto new_tpos = tpos + DIRECTIONS[j];
                info.legal_actions[i][j] = walls[at(new_tpos)] == 0 || new_tpos.x < 0 || new_tpos.x == MAP_WIDTH;
            }
        }
    }
}

GameState::~GameState()
{
    if (foods) {
        delete[] foods;
    }
}

GameStateInfo GameState::start_new_game(const int* walls, int* foods) {
    GameStateInfo info;
    info.state.reset(new GameState(walls, foods));
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


