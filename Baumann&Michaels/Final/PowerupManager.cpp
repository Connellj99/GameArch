#include "PowerupManager.h"

PowerupManager::PowerupManager(UnitManager* newManager, int offset, int newScreenWidth, int newScreenHeight, int newScreenPadding)
{
	manager = newManager;
	powerupCollisionOffset = offset;
	screenWidth = screenWidth;
	screenWidth = newScreenWidth;
	screenHeight = newScreenHeight;
	screenPadding = newScreenPadding;
	maxPowerupTime = 10.0;
}

void PowerupManager::addPowerupToGame(string powerup)
{
	Powerup* powerupToAdd;
	for (auto toSpawn : mPowerupToSpawnList)
	{
		if (toSpawn->getName() == powerup)
		{
			powerupToAdd = toSpawn;
			break;
		}
	}

	mPowerupList.push_back(powerupToAdd);

	random_device dev;
	mt19937 rng(dev());

	uniform_int_distribution<std::mt19937::result_type> distWidth(screenPadding, screenWidth);
	uniform_int_distribution<std::mt19937::result_type> distHeight(screenPadding, screenHeight);

	int newWidth = distWidth(rng);
	int newHeight = distHeight(rng);

	powerupToAdd->getThisUnit()->updateLocation(newWidth, newHeight);

	manager->addToStorageNoClear(powerupToAdd->getThisUnit());
}

void PowerupManager::addPowerupToBuffer(Powerup* powerup)
{
	mPowerupToSpawnList.push_back(powerup);
}

void PowerupManager::setMaxPowerupTime(double time)
{
	maxPowerupTime = time;
}

void PowerupManager::removePowerupFromGame(string powerupName)
{
	int iter = 0;
	for (Powerup* powerup : mPowerupList)
	{
		if (powerup->getName() == powerupName)
		{
			mPowerupList.erase(mPowerupList.begin() + iter);
		}
		iter++;
	}
}

void PowerupManager::removeAllPowerupsFromGame()
{
	mPowerupList.clear();
}

Powerup* PowerupManager::getPowerup(string name)
{
	int iter = 0;
	for (Powerup* powerup : mPowerupToSpawnList)
	{
		if (powerup->getName() == name)
		{
			return mPowerupToSpawnList[iter];
		}
		iter++;
	}

	return NULL;
}

bool PowerupManager::checkPowerupInGame(Powerup* powerup)
{
	return find(mPowerupList.begin(), mPowerupList.end(), powerup) != mPowerupList.end();
}

void PowerupManager::checkAllPowerupsForCollisionWithPlayer() 
{
	int iter = 0;
	for (Powerup* powerup : mPowerupList) 
	{
		
		if (manager->playerCollidedWithPowerup(powerup->getThisUnit(), powerupCollisionOffset)) 
		{
			manager->removePowerupFromStorage(powerup->getThisUnit());
			mPowerupList.erase(mPowerupList.begin() + iter);

			powerup->onTouchEvent();
		}
		iter++;
	}
	
}

void PowerupManager::updatePowerupSpawning(double deltaTime)
{
	timeToSpawn += deltaTime;
	for(Powerup* spawn : mPowerupToSpawnList)
	{
		double frequency = spawn->getSpawnFrequency();
		if (fmod(timeToSpawn, frequency) < 1)
		{
			if (!checkPowerupInGame(spawn))
			{
				addPowerupToGame(spawn->getName());
			}
		}
	}
	
}

void PowerupManager::incrementPlayerLength()
{
	manager->increasePlayerLengthBy(2);
}

PowerupManager::~PowerupManager() 
{
	for (auto i : mPowerupToSpawnList)
	{
		delete i;
	}
}