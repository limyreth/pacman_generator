//////////////////////////////////////////////////////
// Pacman version 4
// Started September 5, 2008
// using C++ & SDL
// ported to linux with attempt at crossplatform compatibility
//////////////////////////////////////////////////////

#pragma once

//#define DIRECTINPUT_VERSION 0x0800

//////////////////////////////////////////////////////
//	INCLUDES
//////////////////////////////////////////////////////

//#include <windows.h>
//#include <d3d9.h>
//#include <d3dx9.h>
//#include <dinput.h>
//#include <dsound.h>
//#include <dxerr.h>

#include <SDL.h>
#include <SDL_rotozoom.h>
#include <SDL_ttf.h>

#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

#include "Settings.h"
#include "Error.h"
//#include "resource.h"
#include "App.h"
#include "Log.h"
#include "Game.h"


//////////////////////////////////////////////////////
//	DEFINES
//////////////////////////////////////////////////////

#define WNDTITLE	"Pacman Revolutions (" __DATE__ ", " __TIME__ ")"
#define CLSNAME		"Pacman Revolutions"

#define STATE_GAME	0
#define STATE_ENTER_HSCORE 1
#define STATE_VIEW_HSCORE 2
#define STATE_MAP_EDITOR 3
#define STATE_STOPPED 4
#define STATE_EDITOR 5

#define MODE_LEVELS 2
#define MODE_SKINS 1

#define UP	0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define ENTER 4
#define SPACE 5
#define CLICK 6

#define MOVEMOD 2000.0f

#define EXTRA_Y_SPACE 50

#define SMALL_DOTS_SCORE 10
#define LARGE_DOTS_SCORE 50

#define SETTINGSFILE "settings.conf"
#define PACCFGFILE "pacman.conf"
#define CFGFILE "level.conf"
#define OBJFILE "objmap"
#define MAPFILE "map"

#define FRUITDURATION 10000
#define BOOSTTIME 3000

#define MAXENTRIES 8

//////////////////////////////////////////////////////
//	DECLARATIONS
//////////////////////////////////////////////////////

//LRESULT CALLBACK WindowProc(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam);
//class Object;

