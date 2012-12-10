/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Main.h"
#include "Game.h"

//////////////////////////////////////////////////////
//	GLOBAL VARS
//////////////////////////////////////////////////////

Log		logtxt;
App		app;


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
        //init log
        logtxt.setFilename(".pacman_sdl");

        // TODO rm set/getQuit, just let them bubble up to here, or further

        //init SDL
        if ( !app.getQuit() ) app.InitApp();

        //init window
        if ( !app.getQuit() ) app.InitWindow();

        //init sound
        if ( !app.getQuit() ) app.InitSound();

        //init game class
        Game game;
        if ( !app.getQuit() ) game.gameInit();

        //main loop
        while ( ! app.getQuit() ) {

            game.emptyMsgPump();

            if ( ! app.getQuit() )
                game.processLogic();

            if ( ! app.getQuit() ) // TODO don't render when generating
                game.render();
        }

        //shutdown
        logtxt.print( "Shutdown" );
    }
    catch (const std::exception& e) {
        app.log_exception(e);
        return 1;
    }

    return 0;
}
