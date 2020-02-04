#pragma once

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <Timer.h>
#include <PerformanceTracker.h>
#include "Trackable.h"
#include "System.h"
#include "Unit.h"
#include "UnitManager.h"
#include "GraphicsBufferManager.h"
#include "EventSystem.h"
#include "EventListener.h"
#include "InputTranslator.h"
#include "PowerupManager.h"
#include "LevelManager.h"
#include <Vector2D.h>

class EventSystem;

class Game :public EventListener
{
private:
	System* mpSys;
	UnitManager* mpUnitManager;
	GraphicsBufferManager* mpGBManager;
	PerformanceTracker* mpPerformanceTracker;
	PowerupManager* mpPowerupManager;
	LevelManager* mpLevelManager;
	Timer mTimer;
	const string mLOOP_TRACKER = "loop";
	int mHeight;
	int mWidth;
	int mMinWidth;
	int mMaxWidth;
	int mMinHeight;
	int mMaxHeight;
	bool mMouseDown = false;
	bool mRightMouseDown = false;
	bool mSwapNow = false;
	bool mExitNow = false;
	int mSpeedUp = 0;
	float mFramesPerSecond;

	bool mIsCleanedUp = false;
	bool mIsInitted = false;
	int* mpCurrentMousePos;

	Font* mainFont;

	// Snake specific variables
	int mPlayerSpeed;

	int* mpPlayerStartingPos;
	int* mpPlayerUpdatedPos;
	int* mpPlayerDirection;

	map<string, Sprite*> mSprites;
	map<string, Animation*> mAnimations;

	vector<Sprite*> mAlwaysDraw; // For backgrounds
	vector<Unit*> mAlwaysAnimate; // For single animations
	vector<Unit*> mSwapOnEnter;

	string mAppleName;
	string mSpeedUpName;
	string mSlowDownName;
	string mBonusPointsName;

	Level* mCurrentLevel;
	int mAppleScore;
	int mBonusScore;

	double mAppleFrequency;
	double mSpeedUpFrequency;
	double mSlowDownFrequency;
	double mBonusFrequency;

	int mGameState = 0; // 0 = title, 1 = main game, 2 = win, 3 = loss
	Sprite* mTitleScreen;
	Sprite* mLossScreen;
	Sprite* mWinScreen;

	Game(Game& game)=delete;
	static Game* mpGameInstance;

	Game();
	Game(EventSystem* pEventSystem, int width, int height, float fps = 60);
	Game(EventSystem* pEventSystem);
	~Game();

	#pragma region Game Data

	string mAssetPath;
	string mBackgroundFilename;
	string mPlayerFilename;
	string mWallFilename; 
	string mBodyFilename; 
	string mAppleFilename; 
	string mSpeedUpFilename; 
	string mSlowDownFilename; 
	string mBonusFilename; 
	string mWelcomeScreenFilename; 
	string mWinScreenFilename; 
	string mLossScreenFilename; 
	string mWallUnitName;
	int mNumberOfLevels;

	#pragma endregion

	#pragma region HelperFunctions
	void InitBoilerplateVariables();
	void resetPlayerDirection();
	void resetPlayerPosition();
	void updateMouseLocation(Vector2D newMouseLocation);
	void drawBackgroundImages(const float &UNIT_SCALE);
	void removeAtMouseCoordsIfRightMouseDown();
	void swapUnitsOnEnter();
	void speedUpUnitsOnKeyPressed();
	void updateLocationsAndDrawAllUnits(const float &UNIT_SCALE, const int &MOUSE_OFFSET);
	void placePlayerAtNewLocation();
	void updatePlayerPositionBasedOnDirection(const int &BOUNDARY_OFFSET);
	void gameOver();
	void instantiateUnitsOnMouseDown(const int &MOUSE_OFFSET);
	void updateUnitAnimationsBasedOnElapsedTime(double &lastTime, const float &UNIT_SCALE, const int &MOUSE_OFFSET);
	void waitForInputOrEndOfFrame();
	void displayFPS();
	void beginTimingAndTrackingLoop();
	void stopTrackingLoop();
	void flipSystemGraphicsBuffer();
	#pragma endregion

public:

	void handleEvent(const Event& theEvent);
	void handleMouseEvent(const Event& theEvent);
	
	void handleKeyEvent(const Event& theEvent);

	void gameTitle();

	void startGame();

	void resetWallLocations();

	void loadNewWalls();

	void updatePlayerDirection(int x, int y);

	void setPlayerSpeed(int speed);

	void createBoundariesFromFile(string unitName, string filePath);
	void createWallFromFile(string unitName, string filePath, int offset);
	void createWallAtLocation(string unitName, int xPos, int yPos);

	void addRandomlySpawningApple(string unitName);
	void addRandomlySpawningSpeedUp(string unitName);
	void addRandomlySpawningSlowDown(string unitName);
	void addRandomlySpawningBonusPoints(string unitName);

	void handlePowerupEvent(const Event& theEvent);
	void createBuffer(string bufferName, string filename, int width, int height);
	void createAnimation(string bufferName, string filename, int dimensions);
	void createUnit(string unitName);
	void swapOnEnter(string unitName);
	void makeControllable(string unitName, string bodyName);
	void addAnimationToUnit(string unitName, string animationName);
	void drawBackground(string bufferName, int x, int y, float scale = 1.0f);
	void drawUnitAtMouse(string unitName);
	void createOnMouseDown(string unitName);
	void InstantiateAtMouse(Unit* unitName, int offset);
	static void createInstance(EventSystem* pEventSystem, int width, int height, int FPS);
	static Game* getInstance();
	static void cleanupInstance();
	void cleanup();

	void loadDataFromFile(string filePath);

	void init();

	void loadLevelsFromFiles();

	void createLossScreen(const std::string &LOSS_SCREEN_BUFFERNAME);

	void createWinScreen(const std::string &WIN_SCREEN_BUFFERNAME);

	void createWelcomeScreen(const std::string &WELCOME_SCREEN_BUFFERNAME);

	void updateDataFromCurrentLevel();

	void checkPlayerLength();

	void gameWin();

	void resetGame();

	void createNewLevel();
	
	void doLoop();

	void drawLossScreen(const float &UNIT_SCALE);

	void drawWinScreen(const float &UNIT_SCALE);

	void drawTitleScreen(const float &UNIT_SCALE);

	void playMainGameLoop(const int &BOUNDARY_OFFSET, double &lastTime, const float &UNIT_SCALE, const int &MOUSE_OFFSET);

	

	

	

	

	

	

	

	

	

	

	

	

	

	

};

#endif
