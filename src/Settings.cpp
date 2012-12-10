/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Settings.h"

extern Log logtxt;

string Settings::getFile(string filename) {
    struct stat fileInfo;
    for(int i = 0; i < searchpaths.size(); i++) {
        string path = searchpaths[i] + "/" + filename;
        if (stat(path.c_str(), &fileInfo) == 0) {
            return path;
        }
    }
    throw_exception("File not found: " + filename);
}

Settings::Settings() 
:   TICK_RATE(60),
    tilesize(20),
    PLAYER_SIZE(2.0 * tilesize * 0.8),
    VULNERABLE_TICKS(6 * TICK_RATE),
    FRUIT_TICKS(10 * TICK_RATE),
    LEVEL_PATH("./levels/0/"),
    SKINS_PATH("./skins/0/"),
    fieldwidth(28),
    fieldheight(31),
    pacstartx(13),
    pacstarty(23),
    baddiestartx(13),
    baddiestarty(13),
    full_speed(9.5 * tilesize / TICK_RATE),
    width(fieldwidth * tilesize),
    height(fieldheight * tilesize)
{

    searchpaths.push_back(".");
    searchpaths.push_back(string(getenv("HOME")) + "/" HOME_CONF_PATH);
    searchpaths.push_back(APP_PATH);
}
