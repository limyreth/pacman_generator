/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <pacman/gui/GUI.h>
#include <pacman/model/Action.h>

#include <list>
#include <vector>

namespace PACMAN {

    struct GUIMainArgs {
        GUI::GUIArgs gui_args;
        std::vector<std::vector<MODEL::Action>> paths;
        bool pause_at_end;
        int quit_at_step;
        int player_index;
    };

    class GUIMain {
    public:
        void run(const GUIMainArgs&);
    };

}
