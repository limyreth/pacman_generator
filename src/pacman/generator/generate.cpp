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
#include "../Error.h"
#include "../Utility.h"

#include <fstream>
#include <sstream>
#include <cstdlib>

#include <sys/stat.h>
#include <dirent.h>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ios;

namespace PACMAN {
    namespace GENERATOR {

/*
 * Returns 0 if no file found, returns number of state file otherwise
 *
 * Note that each state file name is just a number >= 1
 */
int find_previous_state(const string STATE_DIR) {
    DIR* dir = opendir(STATE_DIR.c_str());

    if (!dir) {
        throw_exception("Could not open STATE_DIR");
    }

    // find file with largest number
    dirent* entry;
    int max_number = 0;
    while (entry = readdir(dir)) {
        std::stringstream str;
        str << entry->d_name;
        int num;
        str >> num;
        if (!str.fail() && num > max_number) {
            max_number = num;
        }
    }

    closedir(dir);

    return max_number;
}

string get_state_path(const string STATE_DIR, int number) {
    return STATE_DIR + "/" + to_string(number);
}

void run_generate() {
    std::shared_ptr<GeneratorRun> run;
    const string STATE_DIR = string(getenv("XDG_DATA_HOME")) + "/pacman_generator";
    mkdir(STATE_DIR.c_str(), 0755);

    int previous_state_number = find_previous_state(STATE_DIR);
    if (previous_state_number > 0) {
        cout << "Loading save state " << previous_state_number << endl;
        std::ifstream in(get_state_path(STATE_DIR, previous_state_number), ios::in | ios::binary);
        run.reset(new GeneratorRun(in));
    }
    else {
        cout << "No save state found, starting new run" << endl;
        run.reset(new GeneratorRun);
    }
    run->start();

    bool quit = false;
    while (!quit) {
        string input;
        cin >> input;
        if (input == "quit" || input == "q") {
            quit = true;

            cout << "Stopping generator" << endl;
            std::ofstream out(get_state_path(STATE_DIR, previous_state_number + 1), ios::out | ios::binary);
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
