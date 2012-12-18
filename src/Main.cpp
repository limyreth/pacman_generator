/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

//////////////////////////////////////////////////////
// Pacman version 4
// Started September 5, 2008
// using C++ & SDL
// ported to linux with attempt at crossplatform compatibility
//////////////////////////////////////////////////////

#include "Game.h"
#include "Log.h"

//////////////////////////////////////////////////////
//	GLOBAL VARS
//////////////////////////////////////////////////////

Log		logtxt;

//////////////////////////////////////////////////////
//	MAIN
//////////////////////////////////////////////////////

int main( int argc, char** argv ) {
    std::string str="";

    for (int i = 1;i<argc;i++) {
        str=argv[i];
        if (str=="--help") {
            std::cout << "pacman usage:\n\ncommandline arguments\n--help:\t\tshow this message\n"
                    << "--skin <skin>:\tstart with selected skin\n"
                    << "ingame\nesc/q:\tquit\narrows:\tmovement\n"
                    << "p:\ttoggle pause\nn:\tnew game\n"
                    << "f:\ttoggle fps display\n";
            return 0;
        }
        else
            std::cerr << "unrecognized commandline option\n";
    }

    srand( (unsigned int)time(NULL) );

    try {
        logtxt.setFilename(".pacman_sdl");

        Game game;
        game.gameInit();

        //main loop
        while (game.emptyMsgPump()) {
            game.processLogic();
            game.render();// TODO don't render when generating
        }

        //shutdown
        logtxt.print( "Shutdown" );
    }
    catch (const std::exception& e) {
        logtxt.log_exception(e);
        return 1;
    }

    return 0;
}
