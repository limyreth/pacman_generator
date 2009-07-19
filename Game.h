#pragma once
#include "Sounds.h"
#include "Main.h"
#include "BckgrObj.h"
#include "Object.h"
#include "Pacman.h"
#include "Ghost.h"
#include "hScore.h"

#define NUMOFOBJECTS 6

class Sounds;


class Game
{
public:
	Game();
	~Game();

	bool loadFont();
	bool loadSprites();
	bool loadMap(std::string file, int* memmap);

	void getMaps( int **m, int **o);
	void render();
	void renderNormal();
	void renderEnterHscore();
	void renderViewHscore();

	std::string getFPS();

	void processInput(int k, int ix = -1, int iy = -1);
	void processLogic();
	void logicGame();
	void logicEnterHscore();

	void resetLvl();
	void nextLvl();
	void gameInit(std::string level="", std::string skin="", bool editor=false);

	bool pause();
	void boost();

	int  getState() { return state; }
	void setState( int st);

	void toggleFps() { showfps = !showfps; }

	void clearHscore();

 	bool isinit;

	void toggleSound();
	void emptyMsgPump();
	void changeSkin();

	void initEditor();
	void renderEditor();
	void logicEditor();
	void editorSave();
	void setEditorPath(std::string path) {editorpath=path;}

	void PrepareShutdown();

private:
	int		state,
			counter;

	std::string	fps;

	SDL_Rect	fpsbox,
                scorebox,
                floatingscorebox;

	unsigned int	ticks;

	TTF_Font	*font;
/*
	ID3DXSprite	*sprite; //still need to add onlostdevice and onresetdevice
*/
	Object		*objects[NUMOFOBJECTS];

	///////////////////////
	// GAME OBJECTS
	//////////////////////

	int		*map,
			*objmap,
			key,
			score,
			deadghostcount,	//used to multiplay score for eating ghosts
			lives,
			objscore,
			floatingX,
			floatingY,
			floatingscore,
			floatingscorecounter,
			specialspawntime,
			level,
			namecol[3],
			hscoreselection;
	unsigned int soundcounter,
            time,
			oldtime,
			ghosttick,
			fruittick,
			pausetick,
			boosttick;
	bool	inputwaiting,
			gamestarted,
			vulnflag,
			specialspawned,
			specialeaten,
			specialhasbeenspawned,
			ispaused,
			isboosted,
			boostavailable,
			levelcleared,
			showfps,
			renderisbusy;
	std::string num[10],
				name;
	hScore	hscore;
	Sounds	*sounds;

	//////////////////////////////////
	// EDITOR OBJECTS
	//////////////////////////////////

	int activetool,
		mouseX,
		mouseY;
	std::string editorpath;

};
