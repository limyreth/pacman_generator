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

    namespace MODEL {

        typedef std::array<GhostState, GHOST_COUNT> Ghosts;

        class GameStateObserver;

        // implementation independent view of a GameState
        /*
         * Positions of external game state are multiplied by GUI::TILE_SIZE
         */
        struct ExternalGameState {
            SPECIFICATION::Foods foods;
            int score;
            int lives;
            PacmanState pacman;
            Ghosts ghosts;
            bool is_fruit_spawned;
            bool is_game_over;
        };

        /*
         * Each GameState shows the state at the begin/end of a tick
         *
         * Progresses game state according to the rules in the specification (see README)
         */
        class GameState : public ASSERTION::Assertable
        {
        public:
            enum State {
                NEW_GAME = 0,
                INITIALISED = 1, // after init_successor
                TIME_PROGRESSED = 2, // after progress_timer
                INITIAL_MOVED = 3, // after initial_movement
                ACTED = 4, // after act
                TRANSITIONING = 5, // during any of the 4 above function calls
                INVALID = 6
            };

        public:
            // create bogus state
            GameState();

            GameState(const GameState& );

            // create new game
            GameState(const Node& pacman_spawn, const std::vector<Node*> ghost_spawns);

            /*
             * To create successor of state: Copy the predecessor and call these in order.
             *
             * State of the game 1 tick after `state`.
             */
            void init_successor(const GameState& predecessor);
            bool progress_timers(const GameState& predecessor, GameStateObserver& uihints);
            void initial_movement(const GameState& predecessor, GameStateObserver& uihints, float movement_excess[]);
            bool act(const std::vector<Action>& actions, const GameState& predecessor, GameStateObserver&, const float movement_excess[]);

            //
            bool operator==(const GameState&) const;
            bool operator!=(const GameState& o) const {
                return !(o == *this);
            }

            bool is_equivalent_to(const ExternalGameState&) const;

            void print(std::ostream&, std::string line_prefix) const;

            unsigned int get_vulnerable_ghost_count() const;

            bool is_fruit_spawned() const;
            int get_level() const;
            int get_score() const;
            int get_lives() const;
            bool is_game_over() const;
            const PlayerState& get_player(unsigned int index) const;
            PlayerState& get_player(unsigned int index);
            const SPECIFICATION::Foods& get_foods() const;
            int get_food_count() const;

        protected:
            void invariants() const;

        private:
            bool did_pacman_lose() const;
            bool did_pacman_win() const;

            void resetLvl();
            void nextLvl();

            int get_food_count_() const;
            int get_fruit_score() const;

            bool is_elroy1(unsigned int ghost_index) const;
            bool is_elroy2(unsigned int ghost_index) const;

            float get_speed(unsigned int player_index);

        private:
            PacmanState pacman;
            Ghosts ghosts;

            SPECIFICATION::Foods foods; // shows where food lies on the map
            int food_count;
            int score;
            int lives;
            int ghost_score;  // score given for eating a ghost

            bool ate_energizer;
            bool triggered_fruit_spawn; // an action was performed which will cause fruit to spawn next tick

            int vulnerable_ticks_left;  // how many more ticks ( / successing game states) ghosts will be vulnerable
            int fruit_ticks_left;  // amount of ticks left til fruit disappears
            int idler_ticks_left;  // ticks left til pacman gets off his lazy ass and starts moving again (pacman rests after eating dot or energizer)
            int ghost_release_ticks_left;  // ticks until we are forced to release a ghost

            State state;
        };

    }
}
