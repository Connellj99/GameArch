#pragma once
#include "LevelManager.h"
#include "Trackable.h"
#include "UnitManager.h"
#include "SnakeManager.h"
#include "GraphicsBufferManager.h"
#include "EventListener.h"
#include "InputTranslator.h"
#include "InputSystem.h"
#include <vector>
#include "Timer.h"
#include "OnScreenText.h"


using namespace std;

class Game : public EventListener
{
public:

 	static Game* getInstance();
	static void initInstance();
	static void cleanupInstance();

	void init(Vector2D screenSize, float targetFrameRate);
	void cleanup();


	void doLoop();
	bool checkIfStillLoop() { return mLoopGame; }
	void hasWon() { isPlaying = 2; };
	void hasLost() { isPlaying = 3; };
	void checkCollision(Vector2D pos);
	
	System* getSystem();

private:
	Game();
	~Game();

	void readGameFile();

	static Game* mpsGameInstance;
	InputSystem* mpInputSystem;
	InputTranslator* mpInputTranslator;


	//Mangers
	SnakeManager mSnakeManager;
	GraphicsBufferManager mBufferManager;
	UnitManager mUnitManager;
	LevelManager mLevelManager;
	OnScreenText *mOnScreenText;
	

	//Event System Classes

	//Change check input to  call inut system udate
	//that fires events and then you dot need to keep checking
	// fair game to call funtions from input system in game

	void render();
	void update();

	System *mSystem;
	Timer mTimer;
	Timer mFoodTimer;
	Timer mPowerTimer;
	double mframeTime;
	Vector2D mScreenSize;

	

	//This does not allow copies of the Game, only passes by referance or gives liker error
	Game(Game& game)=delete; // this should never have deffinition as it was deleted, compilerwill stop and not allow you to copy as constutor has been invialidated
	void operator=(const Game& game);

	//Funtion for on event triggers
	void handleEvent(const Event& theEvent);
	void createNewUnit(Vector2D loc);
	void deleteUnitAtLoc(Vector2D loc);
	void exitDoloop();

	void checkForItemSpawn();
	void spawnFood();
	void spawnPower();
	int getCurrentFPS();


	//Text Info
	Color mTextColor;
	float mCurrentMiliPerFrame;

	//Points and game values
	int isPlaying;
	float mPowerInterval;
	int mStartingSegs;

	//Loop info
	bool mLoopGame = true;

	//File Names
	string FOOD_FILENAME;
	string SLOW_FILENAME;
	string SPEED_FILENAME;
	string SNAKE_FILENAME;
	string BACKGROUND_FILENAME;
	string TEXT_FILENAME;
	//Map Keys
	const string FOOD_KEY = "food";
	const string SLOW_KEY = "slow";
	const string SPEED_KEY = "speed";
	const string SNAKE_KEY = "snake";
	const string BACKGROUND_KEY = "bg";

	Sprite* mpBackgroundSprite = nullptr;

	//Basic Info
	const string MILLER_FILE_PATH = "..\\..\\Roman.Miller\\midterm\\"; //this is for finding the text file of where to laod in all the info 
	string ASSET_PATH;

	const Vector2D SPRITE_LAYOUT= Vector2D(1, 1);
	const Vector2D SPRITE_SIZE = Vector2D(50, 50);

	const string TRACKER = "Loop_Time";

};
