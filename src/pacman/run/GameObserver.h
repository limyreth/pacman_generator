/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

namespace PACMAN {

    namespace MODEL {
        class GameState;
    }

    namespace RUN {

        /*
         * Observes a Game and lets it know how to proceed
         */
        class GameObserver
        {
        public:
            /*
             * Notification after each step
             */
            virtual void finished_step(const ::PACMAN::MODEL::GameState& state) = 0;

            /*
             * Returns True if the game should stop. Called before each step
             */
            virtual bool should_stop() = 0;

            virtual bool is_paused() = 0;
        };

    }
}
