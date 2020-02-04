#pragma once
#include "EventListener.h"
#include "SnakeUnit.h"
#include "System.h"
#include "EventSystem.h"
#include "Animation.h"
#include "Unit.h"
#include "UnitManager.h"
#include "GraphicsBufferManager.h"
#include "InputTranslator.h"
#include "TileTypes.h"
#include <vector>
#include "LevelOutline.h"
#include <fstream>
#include <map>
#include "LevelManager.h"

class LevelOutline;


struct PowerUpSpaces : public Trackable 
{
	string type;
	string version;
	float spawnRate;

	PowerUpSpaces(string key, string tileType, float spawn)
	{
		type = key;
		version = tileType;
		spawnRate = spawn;
	}

};


class LevelCreation : public LevelOutline 
{
public:
	LevelCreation();
	~LevelCreation();

	void init(System* system, string level, string fileName, int rows, int cols);
	void reset();
	void cleanup();
	void update(double time);
	void render();

	void initGrid(int rows, int cols);
	void initWall(Vector2D loc);
	void initFood(Vector2D loc);
	void initSpeedDown(Vector2D loc);
	void initSpeedUp(Vector2D loc);
	void initExtraPoints(Vector2D loc);
	void initSnake(Vector2D loc);
	void initSettings();

	void collisionCheck();

	void placePowerUps();
	void drawText();
	void drawFrameRate(double frameRate);

	Vector2D randomPositionGenerator();

	void readDataFile(string fileName);

	void handleEvent(const Event& theEvent);

private:
	System* mpSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	UnitManager* mpUnitManager;
	SnakeUnit* mpSnakeUnit;
	Font* mpFont;

	bool mIsInit = false;
	bool mExitLevel = false;

	map<string, float> mDataMap;
	vector<vector<TileTypes>> mGameSpace;
	vector<Vector2D> mSnakePositions;
	vector<Vector2D> mWallPositions;
	vector<PowerUpSpaces> mPowerUpSpaces;
	vector<string> mBufferKeys;
	int cellSize;
	int mRows;
	int mCols;
	int mCellWidth;
	int mCellHeight;
	int mScore = 0;
	int mFoodScore = 5;
	int mExtraPointsScore;
	int mPowerUpTimer;
	float mPowerUpTimeTracker;
	int mSnakeWinLength = 7;
	float mSnakeSpeed;
	int mFalseDeathCalls;
	string mLevel;
	string mEndLevelName;
	string mFileName;
	string mDataStopperString = "eos";
	string mWallKey;
	string mSnakeKey;
	string mSpeedDownKey;
	string mSpeedUpKey;
	string mExtraPointsKey;
	string mBackgroundKey;
	string mFoodKey;
	int mDataStopperInt = -1;

	std::vector<Sprite*> mpSnakeList;
	std::vector<Sprite*> mpWallList;
	std::vector<Sprite*> mpFoodList;
	std::vector<Sprite*> mpSpeedDownList;
	std::vector<Sprite*> mpSpeedUpList;
	std::vector<Sprite*> mpExtraPointsList;

};

