#include "PowerUpManager.h"

PowerUpManager::PowerUpManager()
{
	mTargetTime = 60;
	mTimeElapsed = mTargetTime;
	mCurrentIndex = 0;
	mPowerTargetTime = 40 * 1000;
	mPowerTimeElapsed = mPowerTargetTime;
}

PowerUpManager::PowerUpManager(double spawnTime)
{
	mTargetTime = 60;
	mTimeElapsed = mTargetTime;
	mCurrentIndex = 0;
	mPowerTargetTime = spawnTime * 1000;
	mPowerTimeElapsed = mPowerTargetTime;
}

PowerUpManager::~PowerUpManager()
{
	removeAndDestroyAllPowerUps();
}

Unit PowerUpManager::getUnit(int index)
{
	return *mPowerUps[index];
}

string PowerUpManager::getUnitType(int index)
{
	return mPowerUps[index]->getType();
}

int PowerUpManager::getSize()
{
	return mPowerUps.size();
}

Vector2 PowerUpManager::getPos(int index)
{
	return mPowerUps[index]->mCurrentLocation;
}

void PowerUpManager::spawnPowerUps(string type,Animation * animationOne, Animation * animationTwo)
{
	createPowerUp(Vector2(400,150),type,false);

	// add both animations to the unit
	addAnimation(getSize() - 1, *animationOne);
	addAnimation(getSize() - 1, *animationTwo);
}

void PowerUpManager::spawnPowerUps(string type, Animation * animationOne)
{
	createPowerUp(Vector2(400, 150), type, false);

	// add both animations to the unit
	addAnimation(getSize() - 1, *animationOne);
}

int PowerUpManager::randomPowerUpSpawnNumber()
{
	int num;
	//generate random num from 0-2
	srand(time(NULL));
	num = (rand() % 3);
	return num;
}

void PowerUpManager::setPowerUpPos()
{
	//assign a random vector2 position for the powerup to move too
	srand(time(NULL));
	mPowerUpPos = Vector2(rand() % (600 - 50) + 50, rand() % (500 - 50) + 50);
}

void PowerUpManager::createPowerUp(Vector2 newPos)
{
	mPowerUps.push_back(new Unit(newPos));
}

void PowerUpManager::createPowerUp(Vector2 newPos,string type)
{
	mPowerUps.push_back(new Unit(newPos,type));
}

void PowerUpManager::createPowerUp(Vector2 newPos, string type, bool moved)
{
	mPowerUps.push_back(new Unit(newPos, type, moved));
}


void PowerUpManager::destroyPowerUp(int index)
{
	delete mPowerUps[index];
	mPowerUps.erase(mPowerUps.begin() + index);;
}

void PowerUpManager::removeAndDestroyAllPowerUps()
{
	for (int i = 0, max = mPowerUps.size(); i < max; i++)
	{
		delete mPowerUps[i];
	}
	mPowerUps.clear();
}

void PowerUpManager::addAnimation(int index, Animation & newAnim)
{
	mPowerUps[index]->setAnimation(newAnim);
}

void PowerUpManager::swapAnimations(int index)
{
	// Is the given index within bounds?
	if (index > -1 && index < getSize())
	{
		// If yes, then swap the animation at the given index
		mPowerUps[index]->swapAnimation();
	}
}

void PowerUpManager::movePowerUp()
{
	for (int i = 0; i < (int)mPowerUps.size() ; i++)
	{
		if (mPowerUps[i]->getMoveStatus() == false)
		{
			mPowerUps[i]->mCurrentLocation = mPowerUpPos;
			mPowerUps[i]->setMoveStatus(true);
		}
	}
	
}

void PowerUpManager::movePowerUp(int index)
{
	mPowerUps[index]->setMoveStatus(true);
	mPowerUps[index]->mCurrentLocation = mPowerUpPos;
}

void PowerUpManager::updatePowerUps(double timeBetweenFrames)
{
	for (int i = 0, max = mPowerUps.size(); i < max; i++)
	{
		mPowerUps[i]->update(timeBetweenFrames);
	}
}

void PowerUpManager::updateSpawn(float timeBetweenFrames)
{
	// The following code subtracts the time that has passed and if
	// enough time has passed, it will change frames
	mPowerTimeElapsed += timeBetweenFrames;

	if (mPowerTimeElapsed >= mPowerTargetTime)
	{
		mCanSpawn = true;
		mPowerTimeElapsed = 0;
	}
}

void PowerUpManager::drawPowerUps()
{
	if (mPowerUps.size() == 1)
	{
		mPowerUps[0]-> draw(mPowerUps[0]->getType());
	}
	else if (mPowerUps.size() > 1)
	{
		for (int i = mPowerUps.size(); i > 0; i--)
		{
			mPowerUps[i-1]->draw(mPowerUps[i-1]->getType());
		}
	}
	
}