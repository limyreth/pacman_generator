/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "GameState.h"
#include "GameStateObserver.h"
#include "Action.h"
#include "Node.h"
#include <pacman/util/util.h>

#include <string.h>
#include <boost/scope_exit.hpp>

using namespace ::PACMAN::SPECIFICATION;

using std::vector;
using std::cout;
using std::endl;
using std::string;
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

GameState::GameState(const GameState& s)
:   pacman(s.pacman),
    ghosts(s.ghosts),
    foods(s.foods),
    food_count(s.food_count),
    score(s.score),
    lives(s.lives),
    ghost_score(s.ghost_score),
    ate_energizer(s.ate_energizer),
    triggered_fruit_spawn(s.triggered_fruit_spawn),
    vulnerable_ticks_left(s.vulnerable_ticks_left),
    fruit_ticks_left(s.fruit_ticks_left),
    idler_ticks_left(s.idler_ticks_left),
    ghost_release_ticks_left(s.ghost_release_ticks_left),
    state(s.state)
{
}

/**
 * Start new game
 */
GameState::GameState(const Node& pacman_spawn, const vector<Node*> ghost_spawns)
:   pacman(pacman_spawn),
    foods(start_foods),
    food_count(MAX_FOOD_COUNT),
    score(0),
    lives(1),
    ghost_score(200),
    ate_energizer(false),
    triggered_fruit_spawn(false),
    vulnerable_ticks_left(-1),
    fruit_ticks_left(-1),
    idler_ticks_left(0),
    ghost_release_ticks_left(MAX_TICKS_BETWEEN_GHOST_RELEASE),
    state(NEW_GAME)
{
    INVARIANTS_ON_EXIT;

    for (unsigned int i=0u; i<GHOST_COUNT; ++i) {
        ghosts.at(i) = GhostState(*ghost_spawns.at(i));
    }

    ghosts.at(GHOST_BLINKY).leave_pen();
    ghosts.at(GHOST_PINKY).leave_pen();
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
bool GameState::progress_timers(const GameState& pre, GameStateObserver& observer) {
    INVARIANTS_ON_EXIT;
    REQUIRE(state == INITIALISED);
    bool allow_reversing = false;
    state = TRANSITIONING;

    // Vulnerable timing
    if (pre.ate_energizer) {
        vulnerable_ticks_left = VULNERABLE_TICKS;

        // Ghosts become vulnerable in this tick
        for (auto& ghost : ghosts) {
            if (ghost.try_become_vulnerable()) {
                allow_reversing = true;
            }
        }

        ghost_score = 200;
    }
    else if (vulnerable_ticks_left == 0) {
        observer.ghosts_no_longer_vulnerable();

        // Ghosts no longer vulnerable, make it so
        for (auto& ghost : ghosts) {
            if (ghost.become_invulnerable()) {
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
    fruit_ticks_left = max(fruit_ticks_left - 1, -1);

    ENSURE(pre.triggered_fruit_spawn == (fruit_ticks_left == FRUIT_TICKS - 1));
    ENSURE(fruit_ticks_left == -1 || fruit_ticks_left == FRUIT_TICKS - 1 || fruit_ticks_left == pre.fruit_ticks_left - 1);

    state = TIME_PROGRESSED;
    return allow_reversing;
}

void GameState::initial_movement(const GameState& pre, GameStateObserver& observer, float movement_excess[]) {
    INVARIANTS_ON_EXIT;
    REQUIRE(state == TIME_PROGRESSED);
    state = TRANSITIONING;
    const auto old_fruit_ticks_left = fruit_ticks_left;
    const auto old_vulnerable_ticks_left = vulnerable_ticks_left;

    // Move players
    for (unsigned int player_index = 0u; player_index < PLAYER_COUNT; player_index++) {
        movement_excess[player_index] = get_player(player_index).move(FULL_SPEED * get_speed(player_index), player_index);
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
bool GameState::act(const vector<Action>& actions, const GameState& pre, GameStateObserver& observer, const float movement_excess[]) {
    INVARIANTS_ON_EXIT;
    //REQUIRE(actions.size() == PLAYER_COUNT);
    REQUIRE(state == INITIAL_MOVED || state == NEW_GAME);
    state = TRANSITIONING;
    const auto old_fruit_ticks_left = fruit_ticks_left;
    const auto old_vulnerable_ticks_left = vulnerable_ticks_left;

    BOOST_SCOPE_EXIT(&pre, &old_fruit_ticks_left, &old_vulnerable_ticks_left, this_) {
        ENSURE(this_->state == ACTED);
        ENSURE(this_->foods.at(at(this_->pacman.get_tile_pos())) == Food::NONE || this_->did_pacman_lose());
        ENSURE(pre.food_count - this_->food_count <= 1);
        ENSURE(this_->score >= pre.score);
        ENSURE(this_->lives <= pre.lives);

        // internal contract
        ENSURE(this_->fruit_ticks_left == old_fruit_ticks_left || this_->fruit_ticks_left == -1);
        ENSURE(this_->vulnerable_ticks_left == old_vulnerable_ticks_left);
        if (!this_->is_game_over()) {
            ENSURE(this_->ghost_release_ticks_left == MAX_TICKS_BETWEEN_GHOST_RELEASE || this_->ghost_release_ticks_left == pre.ghost_release_ticks_left - 1);
        }
    } BOOST_SCOPE_EXIT_END

    // finish movement
    for (unsigned int i=0u; i < PLAYER_COUNT; ++i) {
        auto& player = get_player(i);
        if (movement_excess[i] >= 0.0f) {
            player.act(actions.at(i));
            player.move(movement_excess[i], i);
        }
    }

    ///////////////////////////////////////////
    // Handle collisions
    ///////////////////////////////////////////

    bool ate_ghost = false;
    auto pacman_tpos = pacman.get_tile_pos();
    for (auto& ghost : ghosts) {
        if (pacman_tpos == ghost.get_tile_pos()) {
            // collide with ghost
            if (!ghost.is_dead()) {
                if (!ghost.is_vulnerable()) {
                    // pacman gets eaten
                    lives--;

                    observer.ate_pacman();

                    if (get_lives() > 0) {
                        resetLvl();
                    }

                    state = ACTED;
                    return false;
                }
                else if (ghost.is_vulnerable()) {
                    // pacman eats ghost
                    REQUIRE(ghost_score == 200 || ghost_score == 400 || ghost_score == 800 || ghost_score == 1600);
                    score += ghost_score;
                    ghost_score *= 2.0;
                    ghost.die();
                    observer.ate_ghost();
                    ate_ghost = true;
                }
            }
        }
    }

    // collide with food
    bool ate_fruit = false;
    int food_index = at(pacman_tpos);
    if (foods.at(food_index) == Food::DOT) {
        foods.at(food_index) = Food::NONE;
        --food_count;
        score += 10;

        observer.ate_dot();

        ASSERT(idler_ticks_left == 0);
        idler_ticks_left = 1;  // pacman can't move for 1 tick after eating a dot
    }
    else if (foods.at(food_index) == Food::ENERGIZER) {
        foods.at(food_index) = Food::NONE;
        --food_count;
        score += 50;

        ate_energizer = true;
        observer.ate_energizer();

        ASSERT(idler_ticks_left == 0);
        idler_ticks_left = 3;  // pacman can't move for 3 ticks after eating a dot
    }
    else if (is_fruit_spawned() && (pacman_tpos == FRUIT_LEFT_TPOS || pacman_tpos == FRUIT_RIGHT_TPOS)) {
        score += get_fruit_score();
        observer.ate_fruit();
        ate_fruit = true;
        fruit_ticks_left = -1;
        ASSERT(idler_ticks_left == 0);
    }

    unsigned int food_eaten = MAX_FOOD_COUNT - food_count;

    // check whether or not to free some ghosts
    --ghost_release_ticks_left;

    if (pre.food_count != food_count) {
        ghost_release_ticks_left = MAX_TICKS_BETWEEN_GHOST_RELEASE;
    }

    if (ghost_release_ticks_left == 0) {
        if (ghosts.at(GHOST_INKY).is_waiting()) {
            ghosts.at(GHOST_INKY).leave_pen();
        }
        else if (ghosts.at(GHOST_CLYDE).is_waiting()) {
            ghosts.at(GHOST_CLYDE).leave_pen();
        }
        ghost_release_ticks_left = MAX_TICKS_BETWEEN_GHOST_RELEASE;
    }
    else if (food_eaten >= 90 && ghosts.at(GHOST_CLYDE).is_waiting()) {
        ghosts.at(GHOST_CLYDE).leave_pen();
        ghost_release_ticks_left = MAX_TICKS_BETWEEN_GHOST_RELEASE;
    }
    else if (food_eaten >= 30 && ghosts.at(GHOST_INKY).is_waiting()) {
        ghosts.at(GHOST_INKY).leave_pen();
        ghost_release_ticks_left = MAX_TICKS_BETWEEN_GHOST_RELEASE;
    }

    // fruit spawn trigger
    triggered_fruit_spawn = food_count != pre.food_count && (food_eaten == 70 || food_eaten == 170);

    state = ACTED;
    return ate_ghost || ate_fruit;
}

unsigned int GameState::get_vulnerable_ghost_count() const {
    REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
    int count = 0;
    for (auto ghost : ghosts) {
        if (ghost.is_vulnerable())
            count++;
    }
    INVARIANT(count == 0 || vulnerable_ticks_left > -1);
    return count;
}

bool GameState::is_elroy1(unsigned int ghost_index) const {
    REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
    REQUIRE(ghost_index < GHOST_COUNT);
    return ghost_index == GHOST_BLINKY && food_count <= 20;
}

bool GameState::is_elroy2(unsigned int ghost_index) const {
    REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
    REQUIRE(ghost_index < GHOST_COUNT);
    return ghost_index == GHOST_BLINKY && food_count <= 10;
}

int GameState::get_food_count() const {
    return food_count;
}

/*
 * Use food_count instead; it's faster
 */
int GameState::get_food_count_() const {
    int count = 0;
    for (auto food : foods) {
        if (food) {
            count++;
        }
    }
    return count;
}

void GameState::invariants() const {
    INVARIANT(food_count >= 0);
    INVARIANT(!(food_count == 0 && !did_pacman_win()));
#ifndef NDEBUG
    INVARIANT(food_count == get_food_count_());
#endif

    INVARIANT(score >= 0);
    INVARIANT(lives >= 0);

    ENSURE(fruit_ticks_left >= -1);
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

    for (unsigned int i=0u; i < GHOST_COUNT; ++i) {
        if (other.ghosts.at(i) != ghosts.at(i)) {
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
        other.ghost_release_ticks_left == ghost_release_ticks_left &&
        other.ghost_score == ghost_score;
}

bool GameState::is_equivalent_to(const ExternalGameState& o) const {
    if (o.pacman != pacman) {
        return false;
    }

    for (unsigned int i=0u; i < GHOST_COUNT; ++i) {
        if (o.ghosts.at(i) != ghosts.at(i)) {
            return false;
        }
    }

    if (o.foods != foods) {
        return false;
    }

    return o.score == score &&
        o.lives == lives &&
        o.is_fruit_spawned == is_fruit_spawned() &&
        o.is_game_over == is_game_over();
}

void GameState::print(std::ostream& out, string prefix) const {
    pacman.print(out, prefix, "pacman");
    out << endl;
    ghosts.at(GHOST_BLINKY).print(out, prefix, "blinky");
    out << endl;
    ghosts.at(GHOST_PINKY).print(out, prefix, "pinky");
    out << endl;
    ghosts.at(GHOST_INKY).print(out, prefix, "inky");
    out << endl;
    ghosts.at(GHOST_CLYDE).print(out, prefix, "clyde");
    out << endl;

    out << prefix << "ExternalGameState game_state;" << endl
        << prefix << "game_state.score = " << score << ";" << endl
        << prefix << "game_state.lives = " << lives << ";" << endl
        << prefix << "game_state.is_fruit_spawned = " << is_fruit_spawned() << ";" << endl
        << prefix << "game_state.is_game_over = " << is_game_over() << ";" << endl
        ;

    out << endl;
    out << prefix << "game_state.foods = Foods {";
    for (auto it = foods.begin(); it != foods.end()-1; it++) {
        out << "(Food::Type)" << *it << ", ";
    }
    out << "(Food::Type)" << foods.back() << "};" << endl;

    out << endl
        << prefix << "/////////////////////////////////////////////////////////////////////////////////////////" << endl
        << endl
        << prefix << "game_state.pacman = PacmanState(pacman_origin, pacman_destination, pacman_pos);" << endl
        << prefix << "game_state.ghosts = Ghosts {" << endl
        << prefix << "    GhostState(blinky_origin, blinky_destination, blinky_pos, blinky_state, clyde_vulnerable)," << endl
        << prefix << "    GhostState(pinky_origin, pinky_destination, pinky_pos, pinky_state, clyde_vulnerable)," << endl
        << prefix << "    GhostState(inky_origin, inky_destination, inky_pos, inky_state, clyde_vulnerable)," << endl
        << prefix << "    GhostState(clyde_origin, clyde_destination, clyde_pos, clyde_state, clyde_vulnerable)" << endl
        << prefix << "};" << endl
        ;
}

bool GameState::is_fruit_spawned() const {
    REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
    return fruit_ticks_left >= 0;
}

int GameState::get_level() const {
    REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
    return 1;
}

int GameState::get_score() const {
    REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
    return score;
}

int GameState::get_lives() const {
    REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
    return lives;
}

bool GameState::is_game_over() const {
    REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
    return did_pacman_lose() || did_pacman_win();
}

const PlayerState& GameState::get_player(unsigned int index) const {
    if (index == 0u) {
        return pacman;
    }
    else {
        return ghosts.at(index-1u);
    }
}

PlayerState& GameState::get_player(unsigned int index) {
    if (index == 0u) {
        return pacman;
    }
    else {
        return ghosts.at(index-1u);
    }
}

const SPECIFICATION::Foods& GameState::get_foods() const {
    REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
    return foods;
}

bool GameState::did_pacman_lose() const {
    REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
    return lives == 0;
}

bool GameState::did_pacman_win() const {
    REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
    return food_count == 0;
}

int GameState::get_fruit_score() const {
    return 100;
}

float GameState::get_speed(unsigned int player_index) {
    if (player_index == PLAYER_PACMAN) {
        // pacman
        if (idler_ticks_left > 0) {
            idler_ticks_left = max(idler_ticks_left - 1, 0);
            return 0;
        }
        else if (get_vulnerable_ghost_count() > 0) {
            return ENERGETIC_PACMAN_SPEED;
        }
        else {
            return NORMAL_PACMAN_SPEED;
        }
    }
    else {
        const unsigned int ghost_i = player_index - 1u;
        if (ghosts.at(ghost_i).is_dead()) {
            return DEAD_GHOST_SPEED;
        }
        else if (ghosts.at(ghost_i).is_in_tunnel()) {
            return GHOST_TUNNEL_SPEED;
        }
        else if (ghosts.at(ghost_i).is_vulnerable()) {
            return GHOST_VULNERABLE_SPEED;
        }
        else if (is_elroy2(ghost_i)) {
            return ELROY2_SPEED;
        }
        else if (is_elroy1(ghost_i)) {
            return ELROY1_SPEED;
        }
        else {
            return GHOST_NORMAL_SPEED;
        }
    }
}

}}
