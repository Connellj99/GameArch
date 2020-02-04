#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>

#include <vector>

#include "System.h"
#include "Animation.h"
#include "Unit.h"
#include "UnitManager.h"
#include "GraphicsBufferManager.h"

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

//Alegro key values
const int LEFT_CLICK = 1;
const int RIGHT_CLICK = 2;
const int ESCAPE = 59;
const int F = 6;
const int S = 19;
const int ENTER = 67;
const int SPACE = 75;

//constants
const int DISP_WIDTH = 800;
const int DISP_HEIGHT = 600;
const std::string ASSET_PATH = "..\\..\\shared\\assets\\";
const std::string FOREST_IMAGE = "Woods.png";
const std::string SMURFS_IMAGE = "smurf_sprites.png";
const std::string DEAN_IMAGE = "dean_sprites.png";
const float SCALE_FACTOR = 0.5;
const float SCALE_FACTOR_DEFAULT = 1.0;
const int SMURF_ROWS = 4;
const int SMURF_COLS = 4;
const int SMURF_WIDTH = 60;
const int SMURF_HEIGHT = 60;
const double FRAME_TIME = 16.7;
const std::string WOODS_BUFFER_KEY = "WOODS";
const std::string SMURF_BUFFER_KEY = "SMURF";
const std::string DEAN_BUFFER_KEY = "DEAN";

class Game : public Trackable
{
public:
	static Game* getInstance();
	static void initInstance();
	static void cleanupInstance();

	void init();
	void cleanup();
	void doLoop();
	int getInput();
	void update();
	void render();
	System* getSystem();

private:
	static Game* mpsGame;

	Game();
	~Game();

	bool mIsInit;
	bool mIsMouseDown;
	bool mExitGame;
	bool mKeyboardValues;

	//holds the current input value
	int mInput;

	//checks to see if key has been pressed
	bool mEnterPressed = false;
	bool mSPressed = false;
	bool mFPressed = false;

	System* mpSystem;

	UnitManager* mpUnitManager;
	GraphicsBufferManager* mpGraphicsBufferManager;

	std::vector<Sprite*> mpSmurfList;
	std::vector<Sprite*> mpDeanList;
};
#endif // !GAME_H