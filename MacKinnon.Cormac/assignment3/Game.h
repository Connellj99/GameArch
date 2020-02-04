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

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

class System;
class Animation;
class Unit;

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

class Game : public Trackable
{
public:
	Game();
	~Game();

	void init();
	void cleanup();
	void doLoop();
	void getInput();
	void update();
	void render();
	System* getSystem();

private:
	bool mIsInit;
	bool mIsMouseDown;
	bool mExitGame;
	bool mKeyboardValues;

	//checks to see if key has been pressed
	bool mEnterPressed = false;
	bool mSPressed = false;
	bool mFPressed = false;

	System* mpSystem;

	Animation* mpSmurfAnim;
	Animation* mpDeanAnim;

	GraphicsBuffer* mpWoodsBuffer;
	GraphicsBuffer* mpSmurfBuffer;
	GraphicsBuffer* mpDeanBuffer;

	Unit* mpSmurfObject;

	Sprite* mpWoodsSprite;
};

extern Game* gpGame;
#endif // !GAME_H