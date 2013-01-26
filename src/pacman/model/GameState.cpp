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
 *
 * - 10 points for each dot
 *
 * - 50 points for each energizer (big dot)
 *
 * - 244 dots
 *
 * - 4 energizers
 *
 * - ghosts made vulnerable by energizer for 6 seconds
 *
 * - ghosts eaten: first 200 points, then 400, 800, 1600. Is reset back to 200 upon eating a new energizer.
 *
 * - 2 fruits appear at directly beneath monster pen after 70 and 170 dots. At level 1 they are worth 100 points. They remain for 10sec.
 *   Spec isn't clear about exactly which tile fruit is in, so consider it to be in both tiles underneath the center of the pen.
 *
 * - monster pen leaving: red spawns outside the first time, pink leaves after 0 dots are eaten, blue leaves after 30 dots eaten, orange leaves after 90 dots total eaten. If no dots are eaten for 4 seconds, the next monster leaves the pen. (in level 3 all monsters leave immediately, always, might want to take that level as simplification)
 *
 * - speeds: see the table. Speed is determined solely by the current tile and state of the player. 100% speed = 9.5 tiles per sec.
 *
 * - pacman and ghosts are free to change direction any time. Ghosts and pacman take in a path as AI.
 *
 * - tunnel: wrap when tile pos exits map bounds. Wrap with pixel accuracy.
 *
 * - Original tile size was 8 px, pacman size 10x11 px, ghost size 14x25. 
 *   Simplification: pacman size = ghost size = 0.8 * 2 * tile_size.
 *   Sizes should be relatively correct. Fruit size is more or less the same as
 *   player size.
 *
 * - cornering: pacman can start his turn earlier. As early as when pacman's
 *   bounds touch the intersection tile's bounds. When cornering, pacman will
 *   briefly move through the wall tile neighbouring the intersection. While
 *   doing so, pacman's tile pos is that of the intersection tile, not that of
 *   the wall. This works for lvl1 speeds (player's pixel pos will enter the
 *   wall tile, even at highest speed; the distance spent in the wall tile is
 *   about 0.42 * tile_size).
 *
 * - Players are not allowed to reverse, unless in 2 cases: as pacman,
 *   immediately after having eaten fruit; as any player, immediately after
 *   pacman eats an energizer
 *
 * - Ghost respawn: ghosts respawn at their original spawn location. Except for
 *   blinky, blinky spawns at pinky's location.
 *
 * In our case we'll start with 1 life. Later we'll add more lifes, but first let's solve the simpler problem
 *
 * The above rules only apply to level 1, I'm assuming pacman won't make it through the first level.
 *
 * The game's logic plays at a fixed rate of 60 ticks per second. So the max render rate is 60 frames per second.
 *
 *
 * For full details: http://home.comcast.net/~jpittman2/pacman/pacmandossier.html
 */

#include "GameState.h"
#include "UIHints.h"
#include "Action.h"
#include "Node.h"
#include "../util/util.h"

#include <string.h>

#include <boost/scope_exit.hpp>

using namespace ::PACMAN::SPECIFICATION;

using std::vector;
using std::cout;
using std::endl;

using std::max;

namespace PACMAN {
    namespace MODEL {

/**
 * Default ctor for use in collections. Don't use objects instantiated this
 * way.
 */
GameState::GameState()
:   state(INVALID)
{
}

/**
 * Start new game
 */
GameState::GameState(const Node& pacman_spawn, const vector<Node*> ghost_spawns)
:   food_count(MAX_FOOD_COUNT),
    score(0),
    lives(1),
    fruit_ticks_left(0),
    vulnerable_ticks_left(-1),
    ghost_release_ticks_left(MAX_TICKS_BETWEEN_GHOST_RELEASE),
    idler_ticks_left(0),
    ate_energizer(false),
    triggered_fruit_spawn(false),
    state(NEW_GAME),
    foods(start_foods)
{
    INVARIANTS_ON_EXIT;


    pacman = PacmanState(pacman_spawn);

    for (int i=0; i<GHOST_COUNT; ++i) {
        ghosts[i] = GhostState(*ghost_spawns.at(i));
    }

    ghosts[GHOST_BLINKY].leave_pen();
    ghosts[GHOST_PINKY].leave_pen();
}

void GameState::init_successor(const GameState& pre) {
    INVARIANTS_ON_EXIT;
    REQUIRE(!pre.is_game_over());
    REQUIRE(state == ACTED); //= REQUIRE(was copied from a final state)

    /* Note:
     *
     * The precedence of events while succeeding to next game state must be as follows:
     *
     * - update ghost vulnerability
     * - update fruit spawn
     * - players are moved
     * - ghost collisions
     * - food eating
     *
     * Actual spec does not require this, but if another implementation wants
     * to reuse solutions generated by this project, then this precedence must
     * be maintained as perfect play *might* differ because of it.
     */

    ate_energizer = false;
    triggered_fruit_spawn = false;
    state = INITIALISED;
}

/*
 * Updates timers, executes triggered events, ...
 *
 * Returns true if players are to be given the choice to reverse direction
 */
bool GameState::progress_timers(const GameState& pre, UIHints& uihints) {
    INVARIANTS_ON_EXIT;
    REQUIRE(state == INITIALISED);
    bool allow_reversing = false;
    state = TRANSITIONING;

    // Vulnerable timing
    if (pre.ate_energizer) {
        vulnerable_ticks_left = VULNERABLE_TICKS;

        // Ghosts become vulnerable in this tick
        for (auto& ghost : ghosts) {
            if (ghost.state == GhostState::NORMAL) {
                ghost.state = GhostState::VULNERABLE;
                allow_reversing = true;
            }
        }
    }
    else if (vulnerable_ticks_left == 0) {
        uihints.ghosts_no_longer_vulnerable();

        // Ghosts no longer vulnerable, make it so
        for (auto& ghost : ghosts) {
            if (ghost.state == GhostState::VULNERABLE) {
                ghost.state = GhostState::NORMAL;
                allow_reversing = true;
            }
        }
    }
    vulnerable_ticks_left = max(vulnerable_ticks_left - 1, -1);  // Consume 1 tick of timer

    ENSURE(pre.ate_energizer == (vulnerable_ticks_left == VULNERABLE_TICKS - 1));
    ENSURE(vulnerable_ticks_left == -1 || vulnerable_ticks_left == VULNERABLE_TICKS - 1 || vulnerable_ticks_left == pre.vulnerable_ticks_left - 1);

    // Fruit spawning
    if (pre.triggered_fruit_spawn) {
        // spawn a fruit
        ASSERT(!is_fruit_spawned());  // It is impossible for another fruit to spawn while a previous is still spawned (eating 100 dots should take long enough for this never to happen)
        fruit_ticks_left = FRUIT_TICKS;
    }
    fruit_ticks_left = max(fruit_ticks_left - 1, 0);

    ENSURE(pre.triggered_fruit_spawn == (fruit_ticks_left == FRUIT_TICKS - 1));
    ENSURE(fruit_ticks_left == 0 || fruit_ticks_left == FRUIT_TICKS - 1 || fruit_ticks_left == pre.fruit_ticks_left - 1);

    state = TIME_PROGRESSED;
    return allow_reversing;
}

void GameState::initial_movement(const GameState& pre, UIHints& uihints, double movement_excess[]) {
    INVARIANTS_ON_EXIT;
    REQUIRE(state == TIME_PROGRESSED);
    state = TRANSITIONING;
    const auto old_fruit_ticks_left = fruit_ticks_left;
    const auto old_vulnerable_ticks_left = vulnerable_ticks_left;

    // Move players
    {
        double speed_modifier;

        for (int player_index = 0; player_index < PLAYER_COUNT; player_index++) {
            if (player_index == 0) {
                // pacman
                if (idler_ticks_left > 0) {
                    idler_ticks_left = max(idler_ticks_left - 1, 0);
                    speed_modifier = 0;
                }
                else if (get_vulnerable_ghost_count() > 0) {
                    speed_modifier = ENERGETIC_PACMAN_SPEED;
                }
                else {
                    speed_modifier = NORMAL_PACMAN_SPEED;
                }
            }
            else {
                const int ghost_i = player_index - 1;
                if (ghosts[ghost_i].is_in_tunnel()) {
                    speed_modifier = GHOST_TUNNEL_SPEED;
                }
                else if (ghosts[ghost_i].state == GhostState::VULNERABLE) {
                    speed_modifier = GHOST_VULNERABLE_SPEED;
                }
                else if (is_elroy2(ghost_i)) {
                    speed_modifier = ELROY2_SPEED;
                }
                else if (is_elroy1(ghost_i)) {
                    speed_modifier = ELROY1_SPEED;
                }
                else {
                    speed_modifier = GHOST_NORMAL_SPEED;
                }
            }

            movement_excess[player_index] = get_player(player_index).move(FULL_SPEED * TILE_SIZE * speed_modifier, player_index);
        }
    }
    ENSURE(old_fruit_ticks_left == fruit_ticks_left);
    ENSURE(old_vulnerable_ticks_left == vulnerable_ticks_left);
    state = INITIAL_MOVED;
}

/*
 * Complete player movement, handle collisions, ...
 *
 * actions may contain invalid actions if the respective player won't act this tick
 *
 * Returns true if pacman is to be given the choice to reverse direction
 */
bool GameState::act(const vector<Action>& actions, const GameState& pre, UIHints& uihints, const double movement_excess[]) {
    INVARIANTS_ON_EXIT;
    //REQUIRE(actions.size() == PLAYER_COUNT);
    REQUIRE(state == INITIAL_MOVED || state == NEW_GAME);
    state = TRANSITIONING;
    const auto old_fruit_ticks_left = fruit_ticks_left;
    const auto old_vulnerable_ticks_left = vulnerable_ticks_left;

    BOOST_SCOPE_EXIT(&pre, &old_fruit_ticks_left, &old_vulnerable_ticks_left, this_) {
        ENSURE(this_->state == ACTED);
        ENSURE(this_->foods[at(this_->pacman.get_tile_pos())] == Food::NONE || this_->did_pacman_lose());
        ENSURE(pre.food_count - this_->food_count <= 1);
        ENSURE(this_->score >= pre.score);
        ENSURE(this_->lives <= pre.lives);

        // internal contract
        ENSURE(this_->fruit_ticks_left == old_fruit_ticks_left || this_->fruit_ticks_left == 0);
        ENSURE(this_->vulnerable_ticks_left == old_vulnerable_ticks_left);
        if (!this_->is_game_over()) {
            ENSURE(this_->ghost_release_ticks_left == MAX_TICKS_BETWEEN_GHOST_RELEASE || this_->ghost_release_ticks_left == pre.ghost_release_ticks_left - 1);
        }
    } BOOST_SCOPE_EXIT_END

    // finish movement
    for (int i=0; i < PLAYER_COUNT; ++i) {
        auto& player = get_player(i);
        if (movement_excess[i] >= 0.0) {
            player.act(actions.at(i));
            player.move(movement_excess[i], i);
        }
    }

    ///////////////////////////////////////////
    // Handle collisions
    ///////////////////////////////////////////

    auto pacman_tpos = pacman.get_tile_pos();
    for (auto& ghost : ghosts) {
        if (pacman_tpos == ghost.get_tile_pos()) {
            // collide with ghost
            if (ghost.state == GhostState::NORMAL) {
                // pacman gets eaten
                lives--;

                uihints.ate_pacman();

                if (get_lives() > 0) {
                    resetLvl();
                }

                state = ACTED;
                return false;
            }
            else if (ghost.state == GhostState::VULNERABLE) {
                // pacman eats ghost
                score += (int) pow(2.0, GHOST_COUNT - get_vulnerable_ghost_count()) * 200;
                ghost.die();
                uihints.ate_ghost();
            }
        }
    }

    // collide with food
    bool ate_fruit = false;
    int food_index = at(pacman_tpos);
    if (foods[food_index] == Food::DOT) {
        foods[food_index] = Food::NONE;
        --food_count;
        score += 10;

        uihints.ate_dot();

        ASSERT(idler_ticks_left == 0);
        idler_ticks_left = 1;  // pacman can't move for 1 tick after eating a dot
    }
    else if (foods[food_index] == Food::ENERGIZER) {
        foods[food_index] = Food::NONE;
        --food_count;
        score += 50;

        ate_energizer = true;
        uihints.ate_energizer();

        ASSERT(idler_ticks_left == 0);
        idler_ticks_left = 3;  // pacman can't move for 3 ticks after eating a dot
    }
    else if (is_fruit_spawned() && (pacman_tpos == FRUIT_LEFT_TPOS || pacman_tpos == FRUIT_RIGHT_TPOS)) {
        score += get_fruit_score();
        uihints.ate_fruit();
        ate_fruit = true;
        fruit_ticks_left = 0;
        ASSERT(idler_ticks_left == 0);
    }

    unsigned int food_eaten = MAX_FOOD_COUNT - food_count;

    // check whether or not to free some ghosts
    --ghost_release_ticks_left;

    if (pre.food_count != food_count) {
        ghost_release_ticks_left = MAX_TICKS_BETWEEN_GHOST_RELEASE;
    }

    if (ghost_release_ticks_left == -1) {
        if (ghosts[GHOST_INKY].state == GhostState::WAITING) {
            ghosts[GHOST_INKY].leave_pen();
        }
        else if (ghosts[GHOST_CLYDE].state == GhostState::WAITING) {
            ghosts[GHOST_CLYDE].leave_pen();
        }
        ghost_release_ticks_left = MAX_TICKS_BETWEEN_GHOST_RELEASE;
    }
    else if (food_eaten >= 90 && ghosts[GHOST_CLYDE].state == GhostState::WAITING) {
        ghosts[GHOST_CLYDE].leave_pen();
        ghost_release_ticks_left = MAX_TICKS_BETWEEN_GHOST_RELEASE;
    }
    else if (food_eaten >= 30 && ghosts[GHOST_INKY].state == GhostState::WAITING) {
        ghosts[GHOST_INKY].leave_pen();
        ghost_release_ticks_left = MAX_TICKS_BETWEEN_GHOST_RELEASE;
    }

    // fruit spawn trigger
    triggered_fruit_spawn = food_count != pre.food_count && (food_eaten == 70 || food_eaten == 170);

    state = ACTED;
    return ate_fruit;
}

unsigned int GameState::get_vulnerable_ghost_count() const {
    REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
    int count = 0;
    for (auto ghost : ghosts) {
        if (ghost.state == GhostState::VULNERABLE)
            count++;
    }
    INVARIANT(count == 0 || vulnerable_ticks_left > 0);
    return count;
}

bool GameState::is_elroy1(int ghost_index) const {
    REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
    REQUIRE(ghost_index >= 0);
    REQUIRE(ghost_index < GHOST_COUNT);
    return ghost_index == GHOST_BLINKY && food_count <= 20;
}

bool GameState::is_elroy2(int ghost_index) const {
    REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
    REQUIRE(ghost_index >= 0);
    REQUIRE(ghost_index < GHOST_COUNT);
    return ghost_index == GHOST_BLINKY && food_count <= 10;
}

void GameState::invariants() const {
    INVARIANT(food_count >= 0);
    INVARIANT(!(food_count == 0 && !did_pacman_win()));
    {
        int count = 0;
        for (auto food : foods) {
            if (food) {
                count++;
            }
        }
        INVARIANT(count == food_count);
    }

    INVARIANT(score >= 0);
    INVARIANT(lives >= 0);

    ENSURE(fruit_ticks_left >= 0);
    ENSURE(fruit_ticks_left < FRUIT_TICKS);

    INVARIANT(vulnerable_ticks_left >= -1);
    INVARIANT(vulnerable_ticks_left < VULNERABLE_TICKS);

    INVARIANT(idler_ticks_left >= 0);
    INVARIANT(idler_ticks_left <= 3);

    INVARIANT(ghost_release_ticks_left >= 0);
    INVARIANT(ghost_release_ticks_left <= MAX_TICKS_BETWEEN_GHOST_RELEASE);
}

void GameState::nextLvl() {
    REQUIRE(false); // didn't expect pacman to win vs perfect ghosts
}

void GameState::resetLvl() {	// vars and positions when pacman dies during level
    REQUIRE(false); // we're testing with lives==0 for now
}

bool GameState::operator==(const GameState& other) const {
    if (other.pacman != pacman) {
        return false;
    }

    for (int i=0; i < GHOST_COUNT; ++i) {
        if (other.ghosts[i] != ghosts[i]) {
            return false;
        }
    }

    if (other.foods != foods) {
        return false;
    }

    return other.food_count == food_count &&
        other.score == score &&
        other.lives == lives &&
        other.vulnerable_ticks_left == vulnerable_ticks_left &&
        other.fruit_ticks_left == fruit_ticks_left &&
        other.idler_ticks_left == idler_ticks_left &&
        other.ate_energizer == ate_energizer &&
        other.triggered_fruit_spawn == triggered_fruit_spawn &&
        other.ghost_release_ticks_left == ghost_release_ticks_left;
}

}}
