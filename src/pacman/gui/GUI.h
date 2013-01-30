/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <pacman/run/DirectionPreference.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <memory>

#define NUMOFOBJECTS 6

namespace PACMAN {

    namespace MODEL {
        class GameState;
        class UIHints;
    }

    namespace GUI {

        class Sounds;
        class Object;

        struct GUIArgs {
            bool show_pacman_nodes;
            bool show_ghost_nodes;
            bool show_food;
            bool show_respawn_paths;
            double game_speed;
        };

        class GUI : public ::PACMAN::RUN::DirectionPreference
        {
        public:
            GUI(const MODEL::GameState& state, GUIArgs gui_args);
            ~GUI();

            std::shared_ptr<MODEL::UIHints> create_uihints();
            void render();
            bool emptyMsgPump();
            Direction::Type get_preferred_direction(); // direction the user wants to go in
            bool is_paused();
            void pause();

        private:
            void InitApp();
            void InitWindow();
            void InitSound();
            void loadFont();
            bool loadSprites();
            void loadMap(std::string file, int* memmap);
            void toggleSound();

        private:
            Direction::Type preferred_direction;
            const MODEL::GameState& state;

            Uint32 old_ticks;
            GUIArgs gui_args;
            std::shared_ptr<SDL_Surface> screen;
            std::shared_ptr<Sounds> snd;
            SDL_Rect scorebox;
            TTF_Font *font;
            Object *objects[NUMOFOBJECTS];
            bool paused;
        };

    }
}
