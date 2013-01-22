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
            GameState(const Node* pacman_spawn, const std::vector<Node*> ghost_spawns);

            /*
             * To create successor of state: Copy the predecessor and call these in order.
             *
             * State of the game 1 tick after `state`.
             */
            void init_successor(const GameState& state);
            bool progress_timers(const GameState& state, UIHints& uihints);
            void initial_movement(const GameState& state, UIHints& uihints, double movement_excess[]);
            void act(const std::vector<Action>& actions, const GameState& state, UIHints&, const double movement_excess[]);

            //
            bool operator==(const GameState&) const;
            bool operator!=(const GameState& o) const {
                return !(o == *this);
            }

            bool get_vulnerable_ghost_count() const;

            inline bool is_fruit_spawned() const {
                return fruit_spawned;
            }

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
                return lives == 0;
            }

            inline bool did_pacman_win() const {
                return food_count == 0;
            }

            inline bool is_game_over() const {
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
                return foods;
            }

        protected:
            void invariants() const;

        private:
            void ensure_final_state();

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

            SPECIFICATION::Foods foods; // shows where food lies on the map
            int food_count;
            int score;
            int lives;

            bool fruit_spawned;
            bool ate_energizer;
            bool triggered_fruit_spawn; // an action was performed which will cause fruit to spawn next tick

            int vulnerable_ticks_left;  // how many more ticks ( / successing game states) ghosts will be vulnerable
            int fruit_ticks_left;  // amount of ticks left til fruit disappears
            int idler_ticks_left;  // ticks left til pacman gets off his lazy ass and starts moving again (pacman rests after eating dot or energizer)

            friend class PACMAN::TEST::Test;
        };

    }
}
