/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "interactive.h"
#include "model/Game.h"
#include "Constants.h"

#include <boost/scope_exit.hpp>

using namespace PACMAN;
using namespace MODEL;

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;

namespace PACMAN {

void InteractiveMain::run(GUI::GUIArgs gui_args) {
    Game game(PLAYER_PACMAN);
    GUI::GUI gui(game.get_state(), gui_args);
    shared_ptr<UIHints> uihints = gui.create_uihints();

    BOOST_SCOPE_EXIT(&game) {
       game.print_path(); 
    } BOOST_SCOPE_EXIT_END

    while (gui.emptyMsgPump()) {
        if (game.act(gui.get_preferred_direction(), *uihints)) {
            gui.render();
        }
    }
}

}
