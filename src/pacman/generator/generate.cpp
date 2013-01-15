/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "generate.h"
#include "GeneratorRun.h"

#include <fstream>
#include <cstdlib>

#include <sys/stat.h>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ios;

namespace PACMAN {
    namespace GENERATOR {

void run_generate() {
    std::shared_ptr<GeneratorRun> run;
    const string STATE_DIR = string(getenv("XDG_DATA_HOME")) + "/pacman_generator";
    mkdir(STATE_DIR.c_str(), 0755);

    run.reset(new GeneratorRun);
    run->start();
    cout << "No save state found, started new run" << endl;

    bool quit = false;
    while (!quit) {
        string input;
        cin >> input;
        if (input == "quit" || input == "q") {
            quit = true;

            cout << "Stopping generator" << endl;
            std::ofstream out(STATE_DIR + "/state", ios::out | ios::binary);
            run->stop(out);
            out.close();
            cout << "Stopped" << endl;
        }
        else {
            cout << "Que?" << endl;
        }
    }
}

}}
