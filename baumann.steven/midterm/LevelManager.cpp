#include "LevelManager.h"

LevelManager::LevelManager(int levelIndex)
{
	mLevelIndex = levelIndex;
}

void LevelManager::addLevel(Level* levelToAdd) 
{
	mLevelList.push_back(levelToAdd);
}

Level* LevelManager::getLevel(int index) 
{
	return mLevelList[index];
}

Level* LevelManager::getLevelAtCurrentIndex()
{
	return mLevelList[mLevelIndex];
}

string LevelManager::getCurrentLevelTitle()
{
	return getLevelAtCurrentIndex()->getLevelTitle();
}

int LevelManager::endLevel()
{
	if (mLevelIndex == mLevelList.size() - 1) {
		mLevelIndex = 0;
		return 1; // Game Won
	}
	else {
		mLevelIndex++;
		return 0; // Game Not Won
	}
}

void LevelManager::goToLastLevel()
{
	mLevelIndex = mLevelList.size();
}

void LevelManager::goToStartLevel()
{
	mLevelIndex = 0;
}

void LevelManager::clear()
{
	for (auto level : mLevelList)
	{
		delete level;
	}
	isCleared = true;
}

LevelManager::~LevelManager()
{
	if (!isCleared)
	{
		clear();
	}
	
}