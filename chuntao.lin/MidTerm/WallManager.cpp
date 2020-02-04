#include "WallManager.h"

WallManager::WallManager()
{
}

WallManager::~WallManager()
{
	removeAndDestroyAllWalls();
}

Wall WallManager::getWall(int index)
{
	return *mWalls[index];
}

Vector2 WallManager::getWallPos(int index)
{
	return mWalls[index]->mWallCurrentLocation;
}

int WallManager::getSize()
{
	return mWalls.size();
}

void WallManager::draw()
{
	//draw units from last index to first. This is to make
	//sure that the head is visible and not behind anything
	if (getSize() > 1)
	{
		for (int i = mWalls.size() - 1; i >= 0; i--)
		{
			mWalls[i]->draw();
		}
	}
	else if (getSize() == 1)
	{
		mWalls[0]->draw();
	}

}

void WallManager::createWall(Vector2 newPos)
{
	mWalls.push_back(new Wall(newPos));
}

void WallManager::removeAndDestroyAllWalls()
{
	for (int i = 0, max = mWalls.size(); i < max; i++)
	{
		delete mWalls[i];
	}
	mWalls.clear();
}

void WallManager::spawnWalls(int numWallsWanted,Animation* anim)
{
	//Create segments of the snake
	for (int i = 0; i < numWallsWanted; i++)
	{
		createWall(Vector2((800 / 2) - (10 * i), 600 / 2));
		addAnimation(getSize()-1, *anim);
	}
}

void WallManager::setWallPos()
{
	//assign a random vector2 position for the fruit to move too
	for (int i = 0; i < getSize(); i++)
	{
		srand(time(NULL));
		mWallPos = Vector2(rand() % (800 - 20) + 25, rand() % (600 - 20) + 25);
		moveWall(i);
	}

}

void WallManager::setWallPos(LevelManager* levelManage)
{
	for (int i = 0; i < getSize(); i++)
	{
		mWallPos = levelManage->mvWallPos[i];
		moveWall(i);
	}
}

void WallManager::moveWall(int index)
{
	mWalls[index]->mWallCurrentLocation = mWallPos;
}

void WallManager::addAnimation(int index, Animation & newAnim)
{
	mWalls[index]->setAnimation(newAnim);
}

void WallManager::swapAnimations(int index)
{
}

void WallManager::update(double timeBetweenFrames)
{
	for (int i = 0, max = mWalls.size(); i < max; i++)
	{
		mWalls[i]->update(timeBetweenFrames);
	}
}
