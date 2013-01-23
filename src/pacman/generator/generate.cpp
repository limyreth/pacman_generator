/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "generate.h"
#include "../Error.h"
#include "../Utility.h"

#include <fstream>
#include <sstream>
#include <cstdlib>

#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ios;

extern std::shared_ptr<PACMAN::GENERATOR::GeneratorMain> generator_main;

namespace PACMAN {
    namespace GENERATOR {

/*
 * Returns 0 if no file found, returns number of state file otherwise
 *
 * Note that each state file name is just a number >= 1
 */
int GeneratorMain::find_previous_state() {
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

string GeneratorMain::get_state_path(int number) {
    ASSERT(number > 0);
    return STATE_DIR + "/" + to_string(number);
}

void GeneratorMain::signal_callback(int signum) {
    generator_main->stop();
}

void GeneratorMain::stop() {
    if (generator) {
        cout << "Stopping generator" << endl;
        generator->stop();
    }
}

GeneratorMain::GeneratorMain(const string STATE_DIR)
:   STATE_DIR(STATE_DIR)
{
}

void GeneratorMain::run() {
    signal(SIGTERM, GeneratorMain::signal_callback);
    signal(SIGINT, signal_callback);  // C-c interrupt

    mkdir(STATE_DIR.c_str(), 0755);

    previous_state_number = find_previous_state();
    if (previous_state_number > 0) {
        cout << "Loading save state " << previous_state_number << endl;
        std::ifstream in(get_state_path(previous_state_number), ios::in | ios::binary);
        generator.reset(new GeneratorRun(in));
    }
    else {
        cout << "No save state found, starting new run" << endl;
        generator.reset(new GeneratorRun);
    }

    std::ofstream out(get_state_path(previous_state_number + 1), ios::out | ios::binary);
    generator->join(out);
    out.close();
    cout << "Stopped" << endl;
}

}}
