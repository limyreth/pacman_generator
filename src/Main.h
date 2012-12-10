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

#pragma once

//////////////////////////////////////////////////////
//	INCLUDES
//////////////////////////////////////////////////////

#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>
#include <assert.h>

#include "Settings.h"
#include "Error.h"
#include "App.h"
#include "Log.h"


//////////////////////////////////////////////////////
//	DEFINES
//////////////////////////////////////////////////////

#define WNDTITLE	"pacman_sdl (" __DATE__ ", " __TIME__ ")"

#define STATE_GAME	0
#define STATE_STOPPED 4

#define MODE_LEVELS 2
#define MODE_SKINS 1

#define UP	0
#define RIGHT   1
#define DOWN    2
#define LEFT    3
#define ENTER   4
#define SPACE   5
#define CLICK   6

#define EXTRA_Y_SPACE 50

#define SETTINGSFILE "settings.conf"
#define CFGFILE "level.conf"
#define OBJFILE "objmap"
#define MAPFILE "map"

#define APP_PATH "/usr/share/pacman_sdl"
#define HOME_CONF_PATH ".config/pacman_sdl"

#define MAXENTRIES 8

using std::cout;
using std::cerr;
using std::endl;
