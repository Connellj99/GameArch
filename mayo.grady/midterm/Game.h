#ifndef GAME_H
#define GAME_H
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include <sstream>
#include "Trackable.h"
#include "EventListener.h"

#include "System.h"
#include "Timer.h"
#include "PerformanceTracker.h"
#include "GraphicsBufferManager.h"
#include "UnitManager.h"
#include "GameEvent.h"
#include "InputTranslator.h"
#include "LevelManager.h"

class Unit;
class UnitManager;
class Animation;

//Game constants to keep
const int ZERO = 0;
const float BASE_SCALE = 1.0;
const float HALF_SCALE = 0.5;
const string TRACKER = "loop";
const int CENTER_X = 300;
const int CENTER_Y = 300;
const int NUM_LEVELS = 3;
const string WALL_KEY = "wall";
const string HEAD_KEY = "head";
const string BODY_KEY = "body";
const string BACKGROUND_KEY = "background";
const string FOOD_KEY = "food";
const string BONUS_KEY = "bonus";
const string FAST_KEY = "fast";
const string SLOW_KEY = "slow";
const string HUD_KEY = "hud";


class Game : public EventListener
{
private:
	//static instance
	static Game * mpGameInstance;

	//Event system pointer
	EventSystem * mpEventSystem;

	//input translator object
	InputTranslator * mpTranslator;

	//System object
	System * mpSystem;

	//unit managers
	UnitManager * mpUnitManager;
	UnitManager * mpWallManager;
	UnitManager * mpFoodManager;
	UnitManager * mpPowerUpManager;

	//graphics buffer manager
	GraphicsBufferManager * mpGBManager;

	//Level manager
	LevelManager * mpLevelManager;

	//Other data as necessary
	Animation * mpBodyAnimation;
	Animation * mpHeadAnimation;
	Animation * mpWallAnimation;
	Animation * mpFoodAnimation;
	Animation * mpBonusAnimation;
	Animation * mpFastAnimation;
	Animation * mpSlowAnimation;

	Font * textFont;

	bool mKeepGoing = true;
	Timer mTheTimer;
	
	int mCurrentAnimation = 0;
	bool mIsInitted = false;
	PerformanceTracker * mpTracker;

	//Constructor
	Game(EventSystem* pEventSystem);

	//Destructor
	~Game();

	//snake direction of travel
	string mDirection = "right";

	//snake speed counter:
	//counts the number of frames,
	//at the desired interval the snake moves
	int mSpeedCounter = 0;
	int mSpeed;
	//same kind of thing for spawning power-ups
	int mPowerUpCounter = 0;

	//track the active level
	int mActiveLevel = 1;

	//power-up spawning frequency
	int mPowerUpFreq;

	//snake movement location variables
	Vector2D mNextLoc;
	Vector2D mPreviousLoc;
	Vector2D mNewLoc;

	//scoring and game target values
	int mScore = 0;
	int mTargetSegments = 0;

	double mFPS;

	//bools to track game states
	bool mStartGame = false;
	bool mWin = false;
	bool mLoss = false;
	bool mGameEnded = false;
	bool mPlayAgain = false;

public:
	//Init
	void init();

	//Cleanup
	void cleanup();

	//do loop
		//get user input
		//adjust game state
		//draw current game state
	void doLoop();

	//accessor for system object
	System * getSystem() { return mpSystem; };

	//handles all drawing
	void render();

	//Static functions
	static Game * getInstance() { assert(mpGameInstance != nullptr); return mpGameInstance; };
	static void initInstance() { mpGameInstance = new Game(EventSystem::getInstance()); };
	static void cleanupInstance() { delete mpGameInstance; };

	//event handling
	void handleEvent(const Event& theEvent);

	//snake specific functions
	void moveSnake();
	void checkForCollision(Vector2D target);
	void createSnake();
	void addSegment();

	//spawn border and interior walls
	void spawnWalls();

	//spawn food in random locations
	void spawnFood();

	//check that the spawn location is free
	bool checkSpawn(Vector2D target);
	
	//generate a random, unoccupied location
	Vector2D randomLocation();

	//check for win condition
	void checkWin();

	//spawn one of three power ups at a given interval in a random location
	void spawnPowerUp();

	//apply the effects a power-up when collected
	void applyPowerUp(int type);

	//set the speed to the default level value
	void setSpeed();

	//draw the hud with score title and fps
	void drawHUD(double time);

	//draw a game over screen if the player loses
	void drawLoss();

	//draw a screen to congratulate the player if they win
	void drawWin();

	//draw the title screen with instructions
	void drawStart();
};
#endif !GAME_H