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

namespace PACMAN {

    class InteractiveMain {
    public:
        void run(GUI::GUIArgs, std::list<MODEL::Action> path, bool pause_at_end);
    };

}
