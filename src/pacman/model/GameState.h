/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <boost/utility.hpp>
#include "PacmanState.h"
#include "GhostState.h"
#include "../specification/Food.h"
#include "../Constants.h"
#include "../util/assertion.h"

#include <vector>

namespace PACMAN {

    namespace TEST {
        class Test;
    }

    namespace MODEL {

        class UIHints;
        class IntermediateGameState;

        // Each GameState shows the state at the begin/end of a tick
        class GameState : public ASSERTION::Assertable
        {
        public:
            // create bogus state
            GameState();

            // create new game
            GameState(const Node& pacman_spawn, const std::vector<Node*> ghost_spawns);

            /*
             * To create successor of state: Copy the predecessor and call these in order.
             *
             * State of the game 1 tick after `state`.
             */
            void init_successor(const GameState& predecessor);
            bool progress_timers(const GameState& predecessor, UIHints& uihints);
            void initial_movement(const GameState& predecessor, UIHints& uihints, double movement_excess[]);
            bool act(const std::vector<Action>& actions, const GameState& predecessor, UIHints&, const double movement_excess[]);

            //
            bool operator==(const GameState&) const;
            bool operator!=(const GameState& o) const {
                return !(o == *this);
            }

            unsigned int get_vulnerable_ghost_count() const;

            inline bool is_fruit_spawned() const {
                REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
                return fruit_ticks_left > 0;
            }

            inline int get_level() const {
                REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
                return 1;
            }

            inline int get_score() const {
                REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
                return score;
            }

            inline int get_lives() const {
                REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
                return lives;
            }

            inline bool did_pacman_lose() const {
                REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
                return lives == 0;
            }

            inline bool did_pacman_win() const {
                REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
                return food_count == 0;
            }

            inline bool is_game_over() const {
                REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
                return did_pacman_lose() || did_pacman_win();
            }

            inline const PlayerState& get_player(int index) const {
                if (index == 0) {
                    return pacman;
                }
                else {
                    return ghosts[index-1];
                }
            }

            inline PlayerState& get_player(int index) {
                if (index == 0) {
                    return pacman;
                }
                else {
                    return ghosts[index-1];
                }
            }

            inline const SPECIFICATION::Foods& get_foods() const {
                REQUIRE(state == NEW_GAME || state == ACTED || state == TRANSITIONING);
                return foods;
            }

        protected:
            void invariants() const;

        private:
            void resetLvl();
            void nextLvl();

            inline int get_fruit_score() const {
                return 100;
            }

            bool is_elroy1(int ghost_index) const;
            bool is_elroy2(int ghost_index) const;

        private:
            PacmanState pacman;
            std::array<GhostState, GHOST_COUNT> ghosts;

            SPECIFICATION::Foods foods; // shows where food lies on the map
            int food_count;
            int score;
            int lives;

            bool ate_energizer;
            bool triggered_fruit_spawn; // an action was performed which will cause fruit to spawn next tick

            int vulnerable_ticks_left;  // how many more ticks ( / successing game states) ghosts will be vulnerable
            int fruit_ticks_left;  // amount of ticks left til fruit disappears
            int idler_ticks_left;  // ticks left til pacman gets off his lazy ass and starts moving again (pacman rests after eating dot or energizer)
            int ghost_release_ticks_left;  // ticks until we are forced to release a ghost

            friend class PACMAN::TEST::Test;

            enum State {
                NEW_GAME,
                INITIALISED, // after init_successor
                TIME_PROGRESSED, // after progress_timer
                INITIAL_MOVED, // after initial_movement
                ACTED, // after act
                TRANSITIONING, // during any of the 4 above function calls
                INVALID
            } state;
        };

    }
}
