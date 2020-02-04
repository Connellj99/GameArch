#ifndef GAME_H
#define GAME_H

// Standard Library includes
#include <vector>
#include <fstream>

// Graphics Library includes
#include <System.h>

// Local Project includes
#include "EventListener.h"
#include "InputTranslator.h"

//include Managers
#include "GraphicsBufferManager.h"
#include "LevelManager.h"
#include "UnitManager.h"
#include "FoodManager.h"
#include "WallManager.h"
#include "PowerUpManager.h"
#include "HudUIManager.h"


// Display constant variables
const int DISP_WIDTH = 800;
const int DISP_HEIGHT = 600;

const int MAX_LEVELS = 3;

// Game Performance-related constant variables
const double MAX_TIME_BETWEEN_FRAMES = 16.7;
const int FRAMES_PER_SEC = 1000;//this is so when I get the fps, set this divided by elapsed time to get in my case about 60 fps.

// Asset-related constant variables
const string NAME_OF_BACKGROUND_BUFFER = "Background Buffer";
const string NAME_OF_WALL_BUFFER = "Game Wall Buffer";
const string NAME_OF_PLAYER_SPRITE_SHEET_BUFFER = "Player Sprite Sheet";
const string NAME_OF_GROW_ITEM_SPRITE_SHEET_BUFFER = "Grow Sprite Sheet";
const string NAME_OF_BONUS_ITEM_SPRITE_SHEET_BUFFER = "Bonus Points Sprite Sheet";
const string NAME_OF_SLOW_ITEM_SPRITE_SHEET_BUFFER = "Slow Sprite Sheet";
const string NAME_OF_FAST_ITEM_SPRITE_SHEET_BUFFER = "Fast Sprite Sheet";

// Class Prototypes
class Animation;
class Unit;
class Wall;
class InputTranslator;
class HudUIManager;

class Game : public EventListener
{
public:

	// Initializers
	void init();
	void initializeSystems();
	static void initStaticGameInstance();

	//inits game data for each level

	void initGameDataFile();//init general game data like display and fonts

	//init game data for each level
	void initDataFile1();
	void initDataFile2();
	void initDataFile3();
	
	// Cleanups
	void cleanup();
	static void destroyStaticGameInstance();
	void cleanLevel();//clear variables, snakes, etc.. from a level
	void resetMovement();

	// Actions
	void doLoop();
	void restart();
	void checkSnake();//check on the snake and see if its alive or dead
	void checkDirection();//check the direction unit should be moving

	//Draw
	void render();//renders the background and intro stuff

	//Create
	void createContent();//create just the snake at start, with the first fruit, extra walls and such
	void spawnChosenPowerUp(int choice);//will get the random number to determine which powerup to spawn when calling its manager

	//Adjusters/Mutators
	void addScore() {mGameScore += mScoreAmt;}//add to the players score
	void addScore(int bonusAmt) { mGameScore += bonusAmt; }//add to the players score
	void deductSpeed(int decrement) { mSnakeSpd -= decrement; }//deduct from snake speed
	void incrementSpeed(int increment) { mSnakeSpd += increment; }//add to snake speed

	void handleEvent(const Event& passedEvent);

	// Accessors

	//access the managers and such
	static Game* getStaticInstance();
	System * getCurrentSystem(){ return mpSystem; }

	GraphicsBufferManager * getGraphicBufferManager(){ return mpBufferManager; }
	WallManager * getWallManager() { return mpWallManager; }
	UnitManager * getUnitManager() { return mpUnitManager; }
	FoodManager * getFoodManager() {return mpFoodManager; }
	PowerUpManager * getPowerUpManager() { return mpPowerUpManager; }
	LevelManager * getLevelManager() { return mpLevelManager; }

	Font* getCurrentFont() { return pCurrentLevelFont; }
	Font* getTitleFont() { return pTitleFont; }
	Color* getTitleColor() { return pTitleColor; }

	//Variable accessors
	int getGameScore() { return mGameScore; }
	double getFPS() { return mFPS; }
	

	double getSpriteDisplacementX() { return mSpriteDisplacementX; };
	double getSpriteDisplacementY() { return mSpriteDisplacementY; };

	double getScreenDivisor() { return mScreenDivisorCentering; };
	double getBackgroundScale() { return mBackgroundScalingVal; };

private:

	// Constructors
	Game();
	Game(EventSystem* passedEventSystem);

	// Destructors
	~Game();

	// Functions
	void arrowKeyChoice(string arrowKey);

	// Static instances
	static Game* mpsGameObject;

	//Fonts
	Font* pTitleFont;
	Font* pCurrentLevelFont;

	//Color
	Color* pTitleColor;

	HudUIManager * mpHudManager;

	// Graphics Buffers Manager
	GraphicsBufferManager* mpBufferManager;

	//Unit Manager
	UnitManager * mpUnitManager;

	//PowerUp Manager
	FoodManager* mpFoodManager;

	//Level Manager
	LevelManager* mpLevelManager;

	//Wall Manager
	WallManager* mpWallManager;

	//PowerUp Manager
	PowerUpManager* mpPowerUpManager;

	// Animations

	//Level animations like barricades/walls and player
	Animation * mpWallAnimation;
	Animation * mpPlayerAnimation;

	//Power up animations
	Animation * mpPUBonusAnimation;//PU means power ups
	Animation * mpPUSlowAnimation;//PU means power ups
	Animation * mpPUFastAnimation;//PU means power ups
	Animation * mpPUGrowAnimation;//PU means power ups

	// Systems
	System * mpSystem;

	// Input System
	InputSystem* mpInputSys; 

	//InputTranslator
	InputTranslator* mpInputTrans;

	// Booleans

	bool mIsDisplaying;//if the game is displaying

	bool mInGame = true;//if we are in the game
	bool mStartGame = false;//if we can start the game
	bool mPlayAgain = false;

	//Booleans for arrow/movement input
	bool mMoveLeft = false;
	bool mMoveRight = false;
	bool mMoveUp = false;
	bool mMoveDown = false;

	//ints
	int mNumWalls;
	int mSnakeSpd;
	int mSnakeStartLength;
	int mGameScore;
	int mScoreAmt;
	int mSnakeLengthRequirement;
	int mFPS;

	//Sprite ints
	int mSpriteDisplacementX;
	int mSpriteDisplacementY;
	int mSpritesPerRow;
	int mSpritesPerColumn;

	//Other
	double mScreenDivisorCentering;
	double mBackgroundScalingVal;

	// Power Up Ints
	int mSpawnFrequency;
	int mSlowAmt;
	int mFastAmt;
	int mBonusAmt;

	//Vector2
	Vector2 mWallPos;
	Vector2 mSpriteDimensions;
	Vector2 mUnitPosition;

	//file paths
	string mAssetPath;//path to the shared assets folder
	string mChunAssetPath;//path to chun tao's assets folder
	string mCustomBGName;//path to the snakes game background.
	string mFontName;//name of the font
	string mWallSpriteName;//string that holds name of the wall/obstacle sprite sheet
	string mPlayerSpriteName;//string that holds name of the player sprite sheet
	string mBonusSpriteName;//string that holds name of the bonus powerup sprite sheet
	string mGrowSpriteName;//string that holds name of the grow powerup sprite sheet
	string mSlowSpriteName;//string that holds name of the slow powerup sprite sheet
	string mFastSpriteName;//string that holds name of the fast powerup sprite sheet
};
#endif !GAME_H

