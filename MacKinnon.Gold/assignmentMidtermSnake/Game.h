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
#include "InputTranslator.h"
#include "SnakeUnit.h"
#include "LevelManager.h"
#include "LevelOutline.h"
#include "LevelCreation.h"
#include "StartLevel.h"
#include "EndLevel.h"

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
//const int DISP_WIDTH = 800;
//const int DISP_HEIGHT = 600;
/*const std::string ASSET_PATH = "..\\..\\MacKinnon.Cormac\\assets\\";
const std::string BACKGROUND_IMAGE = "background_texture.jpg";
const std::string SMURFS_IMAGE = "smurf_sprites.png";
const std::string DEAN_IMAGE = "dean_sprites.png";
const std::string SNAKE_IMAGE = "snake.png";
const std::string WALL_IMAGE = "wallAnimated.png";
const std::string FOOD_IMAGE = "foodAnimated.png";
const std::string SPEED_DOWN_IMAGE = "speedDown.png";
const std::string SPEED_UP_IMAGE = "speedUp.png";
const std::string EXTRA_POINTS_IMAGE = "extraPoints.png";
const std::string GAME_FONT = "cour.ttf";
const float SCALE_FACTOR = 1.0;
const float SCALE_FACTOR_DEFAULT = 1.0;
const int SMURF_ROWS = 4;
const int SMURF_COLS = 4;
const int SMURF_WIDTH = 60;
const int SMURF_HEIGHT = 60;
const double FRAME_TIME = 16.7;
const std::string BACKGROUND_BUFFER_KEY = "BACKGROUND";
const std::string START_BUFFER_KEY = "START";
const std::string END_BUFFER_KEY = "END";
const std::string SNAKE_BUFFER_KEY = "SNAKE";
const std::string FOOD_BUFFER_KEY = "FOOD";
const std::string SPEED_DOWN_BUFFER_KEY = "DOWN";
const std::string SPEED_UP_BUFFER_KEY = "UP";
const std::string WALL_BUFFER_KEY = "WALL";
const std::string EXTRA_POINTS_BUFFER_KEY = "POINTS";
const std::string SMURF_BUFFER_KEY = "SMURF";
const std::string DEAN_BUFFER_KEY = "DEAN";*/

const double FRAME_TIME = 16.7;
const int ROWS = 15;
const int COLS = 15;

class Game : public EventListener
{
public:
	static Game* getInstance();
	static void initInstance();
	static void cleanupInstance();

	void init();
	void cleanup() override;
	void doLoop();
	int getInput();
	void update();
	void render();
	
	System* getSystem();

private:
	static Game* mpsGame;

	Game();
	~Game();

	void handleEvent(const Event& theEvent) override;

	//Game(Game& game) = delete; prevents copy constructors by invalidating them according to what was said in class this is just a note for me ignore this when grading

	bool mIsInit;
	bool mIsMouseDown;
	bool mExitGame;
	bool mKeyboardValues;

	int mCellHeight;
	int mCellWidth;

	int mNumLevels;
	int mCurrentLevel;

	//holds the current input value
	int mInput;

	//checks to see if key has been pressed
	bool mEnterPressed = false;
	bool mSPressed = false;
	bool mFPressed = false;

	System* mpSystem;

	//UnitManager* mpUnitManager;
	//GraphicsBufferManager* mpGraphicsBufferManager;

	InputTranslator* mpInputTranslator;

	//SnakeUnit* mpSnakeUnit;

	//std::vector<std::vector<TileTypes> > mGrid;

	std::string mLevel1File = "Level1.txt";
	std::string mLevel2File = "Level2.txt";
	std::string mLevel3File = "Level3.txt";

	int displayWidth = 800;
	int displayHeight = 600;

	StartLevel* mpStart;
	LevelCreation* mpLevel1;
	LevelCreation* mpLevel2;
	LevelCreation* mpLevel3;
	EndLevel* mpEnd;
	//vector<vector<TileTypes> > mGrid; //move to level creator when finishing game
};
#endif // !GAME_H