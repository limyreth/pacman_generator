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
#include "GUI.h"
#include "Log.h"
#include "Tests.h"
#include <sstream>

#include "Constants.h"
#include "Error.h"
#include <fstream>
#define MAPFILE "map"

using std::string;
using std::cout;

void loadMap(std::string file, int* memmap) {
    int i, count=0, size = MAP_HEIGHT * MAP_WIDTH;
    std::string tmp;
    char c('i');
    std::ifstream mp;

    mp.open( file.c_str() );

    if (!mp ) {
        throw_exception(file + " - Loading error");
    }

    for (i=0;i<size;i++) {
        do {
            if ( mp.eof() ) break;
            c=mp.get();
            if (c == '/' ) {	// enable comments in map file by prefixing line with  a slash
                getline(mp, tmp);
                continue;
            }
        }
        while (! (c >= '0' && c <= '9') ) ;
        memmap[i]=c-48;
        count++;
        if (!mp) break;
    }

    if ( mp.is_open() ) mp.close();

    if (count != size) {
        throw_exception(file + " - Loading error");
    }

    logtxt.print(file + " loaded");
}


int main( int argc, char** argv ) {
    std::string str="";

    try {
        for (int i = 1;i<argc;i++) {
            str=argv[i];
            if (str=="--help") {
                std::cout << "pacman usage:\n\ncommandline arguments\n--help:\t\tshow this message\n"
                        << "ingame\nesc/q:\tquit\narrows:\tmovement\n"
                        << "n:\tnew game\n"
                        << "f:\ttoggle fps display\n";
                return 0;
            }
            else if (str == "--test") {
                std::istringstream str(argv[i+1]);
                int index;
                str >> index;
                test(index-1);
                return 0;
            }
            else
                std::cerr << "unrecognized commandline option\n";
        }

        srand( (unsigned int)time(NULL) );

        logtxt.setFilename(".pacman_sdl");

        int walls[MAP_HEIGHT * MAP_WIDTH];
        loadMap(LEVEL_PATH + MAPFILE, walls);

        Game game(walls);
        GUI gui(game);
        shared_ptr<UIHints> uihints = gui.create_uihints();

        //main loop
        while (gui.emptyMsgPump()) {
            gui.render(walls);
            game.step(uihints);
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
