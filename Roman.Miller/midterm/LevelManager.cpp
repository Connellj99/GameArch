#include "LevelManager.h"
#include "Game.h"

LevelManager::LevelManager()
{
	mLevel = 1;
	mCurrentPoints = 0;
}

LevelManager::~LevelManager()
{
}

void LevelManager::setLevelPointValues(int o, int t, int th, int food)
{
	mFirstPoints = o;
	mSecondPoints = t;
	mThirdpoints = th;
	mfoodPoints = food;
}

void LevelManager::checkPoints()
{
	switch (mLevel)
	{
	case 1:
		if (mCurrentPoints >= mFirstPoints)
		{
			mLevel++;
		}
		break;
	case 2:
		if (mCurrentPoints >= mSecondPoints)
		{
			mLevel++;
		}
	case 3:
		if (mCurrentPoints>=mThirdpoints)
		{
			Game::getInstance()->hasWon();
		}
	}
}
