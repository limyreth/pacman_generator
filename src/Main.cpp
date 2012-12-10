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

using std::exception;

//////////////////////////////////////////////////////
//	GLOBAL VARS
//////////////////////////////////////////////////////

Log		logtxt;
App		app;
Settings settings;


//////////////////////////////////////////////////////
//	MAIN
//////////////////////////////////////////////////////

int main( int argc, char** argv ) {
    std::string str="",level="",skin="",editfile="";

    for (int i = 1;i<argc;i++) {
        str=argv[i];
        if (str=="--help") {
            std::cout << "pacman usage:\n\ncommandline arguments\n--help:\t\tshow this message\n"
                    << "--skin <skin>:\tstart with selected skin\n"
                    << "ingame\nesc/q:\tquit\narrows:\tmovement\n"
                    << "p:\ttoggle pause\nn:\tnew game\ns:\tswitch skin\n"
                    << "f:\ttoggle fps display\n";
            return 0;
        }
        else  if (str=="--skin")
            if (++i<argc) {
            str=argv[i];
            if (str[0]=='-') {
                std::cerr << "no skin name given. exiting...\n";
                return 1;
            }
            else
                skin=str;
        }
        else {
            std::cerr << "no skin name given. exiting...\n";
            return 1;
        }
        else
            std::cerr << "unrecognized commandline option\n";
    }

    srand( (unsigned int)time(NULL) );

    try {
        //init log
        logtxt.setFilename(".pacman_sdl");

        //init settings
        if ( !app.getQuit() ) settings.LoadSettings(SETTINGSFILE); // TODO rm catch all + set/getQuit, just let them bubble up to here, or further
        if ( !app.getQuit() ) settings.LoadSettings( (settings.lvlpath[settings.lvlpathcurrent] + CFGFILE) );

        //init SDL
        if ( !app.getQuit() ) app.InitApp();

        //init window
        if ( !app.getQuit() ) app.InitWindow();

        //init sound
        if ( !app.getQuit() ) app.InitSound();

        //init game class
        Game game;
        if ( !app.getQuit() ) game.gameInit(level,skin);

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
    catch (exception& e) {
        app.log_exception(e);
        return 1;
    }
    catch (exception* e) {
        app.log_exception(*e);
        return 1;
    }

    return 0;
}
