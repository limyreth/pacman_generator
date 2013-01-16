/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "../Directions.h"

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;


#define NUMOFOBJECTS 6

namespace PACMAN {

    namespace MODEL {
        class GameState;
        class UIHints;
    }

    namespace GUI {

        class Sounds;
        class Object;

        class GUI
        {
        public:
            GUI(const MODEL::GameState& state, bool show_pacman_nodes, bool show_ghost_nodes);
            ~GUI();

            shared_ptr<MODEL::UIHints> create_uihints();
            void render();
            bool emptyMsgPump();
            Direction::Type get_preferred_direction(); // direction the user wants to go in

        private:
            void InitApp();
            void InitWindow();
            void InitSound();
            void loadFont();
            bool loadSprites();
            void loadMap(std::string file, int* memmap);

            void renderNormal();

            std::string getFPS();

            void toggleFps() { showfps = !showfps; }

            void toggleSound();

        private:
            Direction::Type preferred_direction;
            const MODEL::GameState& state;

            shared_ptr<SDL_Surface> screen;

            shared_ptr<Sounds> snd;

            int
                    counter;

            std::string
                    fps;

            SDL_Rect
                    fpsbox,
                    scorebox;

            unsigned int
                    ticks;

            TTF_Font
                    *font;

            Object
                    *objects[NUMOFOBJECTS];

            bool showfps;
            bool show_pacman_nodes;
            bool show_ghost_nodes;
        };

    }
}
