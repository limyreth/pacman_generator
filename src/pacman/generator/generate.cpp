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
#include <sstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace PACMAN {
    namespace GENERATOR {

void run_generate() {
    std::shared_ptr<GeneratorRun> run;

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
            std::stringstream str;
            run->stop(str);
            cout << "Stopped" << endl;
        }
        else {
            cout << "Que?" << endl;
        }
    }
}

}}
