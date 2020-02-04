#include "LevelManager.h"

LevelManager::LevelManager(int maxLevels)
{
	mCurrentLevel = 1;
	mTotalLevels = maxLevels;
	mLevelsDone = false;
}

LevelManager::~LevelManager()
{
	cleanUp();
}

void LevelManager::cleanUp()
{
	mLevelLengths.clear();
	mvWallPos.clear();
	mCurrentLevel = 1;
}

void LevelManager::setLevelSnakeRequirements(int requiredNumber)
{
	mLevelLengths.push_back(requiredNumber);
}

void LevelManager::setLevelWallRequirements(Vector2 pos)
{
	mvWallPos.push_back(pos);
}

void LevelManager::checkLevels()
{
	if (mCurrentLevel == mTotalLevels)
	{
		mLevelsDone = true;
	}
}