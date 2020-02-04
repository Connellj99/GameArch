#include "UnitManager.h"

UnitManager::UnitManager() 
{

}

void UnitManager::addUnit(string unitName, Unit* unit) 
{
	mUnits.insert({ unitName, unit });
}

Unit* UnitManager::getUnit(string unitName) 
{
	return mUnits.find(unitName)->second;
}

int UnitManager::getLengthOfPlayer()
{
	return mLengthOfPlayer;
}

int UnitManager::getMaxPlayerLength()
{
	return mNumPlayerSegments;
}

void UnitManager::addToStorage(string unitName) 
{
	mUnitStorage.push_back(getUnit(unitName));
}

void UnitManager::addToStorageNoClear(Unit* unitName)
{
	mUnitStorageNoClear.push_back(unitName);
}

void UnitManager::addToStorage(Unit* unit) 
{
	mUnitStorage.push_back(unit);
}

void UnitManager::addToWallStorage(Unit* unit)
{
	mWallStorage.push_back(unit);
}

void UnitManager::addToBodyStorage(Unit* unit)
{
	mBodyStorage.push_back(unit);
}

void UnitManager::addPlayer(string playerName, string bodyName)
{
	mpPlayer = getUnit(playerName);
	mpBody = getUnit(bodyName);
}
void UnitManager::addPlayer(Unit* player, Unit* body)
{
	mpPlayer = player;
	mpBody = body;
}

void UnitManager::increasePlayerLengthBy(int amount)
{
	mLengthOfPlayer += amount;
}

void UnitManager::increasePlayerLengthAndResetBody(int amount)
{
	mLengthOfPlayer = amount;
	mNumPlayerSegments = 0;
}

void UnitManager::removeFromStorage(Unit* unit)
{
	for (unsigned int i = 0; i < mUnitStorage.size(); i++) 
	{
		if (mUnitStorage[i] == unit) {
			delete mUnitStorage[i];
			mUnitStorage.erase(mUnitStorage.begin() + i);
			break;
		}
	}
}

void UnitManager::removePowerupFromStorage(Unit* unitName)
{
	for (unsigned int i = 0; i < mUnitStorageNoClear.size(); i++)
	{
		if (mUnitStorageNoClear[i] == unitName) {
			mUnitStorageNoClear.erase(mUnitStorageNoClear.begin() + i);
			break;
		}
	}
}

void UnitManager::removeFromBodyStorage(Unit* unit)
{
	for (unsigned int i = 0; i < mBodyStorage.size(); i++)
	{
		if (mBodyStorage[i] == unit) {
			delete mBodyStorage[i];
			mBodyStorage.erase(mBodyStorage.begin() + i);
			break;
		}
	}
}

void UnitManager::deleteUnit(string unitName)
{
	mUnits.erase(unitName);
}

void UnitManager::addAlwaysCreate(string unitName) 
{
	mAlwaysCreate.push_back(getUnit(unitName));
}

void UnitManager::addAlwaysCreate(Unit* unit) 
{
	mAlwaysCreate.push_back(unit);
}

void UnitManager::swapFrozen() 
{
	for (auto i : mUnitStorage)
	{
		i->swapFrozen();
	}
}

void UnitManager::removeAtCoords(int* coords)
{
	for (auto i : mUnitStorage)
	{
		if ((i->getY() >= coords[1] - 30 && i->getY() <= coords[1] + 30) && (i->getX() <= coords[0] + 30 && i->getX() >= coords[0] - 30)) 
		{
			removeFromStorage(i);
		}
	}
}

void UnitManager::incrementLastSpriteAnimation()
{
	mUnitStorage.back()->incrementAnimation();
}

void UnitManager::instantiateAtMouse(bool mouseDown, int* CurrentMousePos, System* drawingSystem, int offset)
{
	for (auto i : mAlwaysCreate)
	{
		if (mouseDown) 
		{
			Unit* newInstance = new Unit(i, CurrentMousePos);
			newInstance->draw(drawingSystem, 1, offset);
			addToStorage(newInstance);
		}
	}
}

int UnitManager::placePlayer(int* playerPosition)
{
	if (mNumPlayerSegments < mLengthOfPlayer) {
		int* oldCoords = new int[2];
		oldCoords[0] = mpPlayer->getX();
		oldCoords[1] = mpPlayer->getY();
		Unit* newInstance = new Unit(mpBody, oldCoords);
		addToBodyStorage(newInstance);
		mNumPlayerSegments++;
	}
	else {
		delete mBodyStorage[0];
		mBodyStorage.erase(mBodyStorage.begin());
		mNumPlayerSegments--;
	}
	
	if (playerCollidedWithBody(60)) {
		return 1; // We collided
	}
	else {
		mpPlayer->updateLocation(playerPosition[0], playerPosition[1]);
		return 0; // We did not collide
	}
	
}

void UnitManager::update(double elapsedTime)
{
	for (auto i : mUnitStorage)
	{
		i->update(elapsedTime);
	}
	for (auto i : mWallStorage)
	{
		i->update(elapsedTime);
	}
	for (auto i : mUnitStorageNoClear)
	{
		i->update(elapsedTime);
	}
	if (mpPlayer != nullptr)
	{
		mpPlayer->update(elapsedTime);
	}
	
}

void UnitManager::addBoundarieBox(string unitName, int minWidth, int maxWidth, int minHeight, int maxHeight, int increments, int offset)
{
	for (int i = minWidth; i < maxWidth; i += increments) 
	{

		int* newParams = new int[2];
		newParams[0] = i;
		newParams[1] = minHeight + offset;
		Unit* newInstance = new Unit(getUnit(unitName), newParams);
		addToStorage(newInstance);
		delete newParams;

		int* newerParams = new int[2];
		newerParams[0] = i;
		newerParams[1] = maxHeight - offset;
		Unit* newerInstance = new Unit(getUnit(unitName), newerParams);
		addToStorage(newerInstance);
		delete newerParams;
	}

	for (int i = minHeight; i < maxHeight; i += increments) 
	{

		int* newParams = new int[2];
		newParams[0] = minWidth + offset;
		newParams[1] = i;
		Unit* newInstance = new Unit(getUnit(unitName), newParams);
		addToStorage(newInstance);
		delete newParams;

		int* newerParams = new int[2];
		newerParams[0] = maxWidth - offset;
		newerParams[1] = i;
		Unit* newerInstance = new Unit(getUnit(unitName), newerParams);
		addToStorage(newerInstance);
		delete newerParams;
	}

}

void UnitManager::addWall(string unitName, int startX, int startY, int endX, int endY, int offset) 
{
	int currentX = startX, currentY = startY;
	while(currentX + offset < endX || currentY + offset < endY)
	{
		int* locationOfNewWallSegment = new int[2];
		locationOfNewWallSegment[0] = currentX;
		locationOfNewWallSegment[1] = currentY;
		Unit* instanceOfNewWallSegment = new Unit(getUnit(unitName), locationOfNewWallSegment);
		addToStorage(instanceOfNewWallSegment);
		mWallLocations.push_back(locationOfNewWallSegment);

		if (currentX + offset < endX)
		{
			currentX += ((endX - startX) / offset) + offset; 
		}
		if (currentY + offset < endY)
		{
			currentY += ((endY - startY) / offset) + offset;
		}

	}
}

void UnitManager::addWallAtPosition(string unitName, int xPos, int yPos)
{
	int* locationOfNewWallSegment = new int[2];
	locationOfNewWallSegment[0] = xPos;
	locationOfNewWallSegment[1] = yPos;
	Unit* instanceOfNewWallSegment = new Unit(getUnit(unitName), locationOfNewWallSegment);
	addToWallStorage(instanceOfNewWallSegment);
	mWallLocations.push_back(locationOfNewWallSegment);
}

bool UnitManager::playerCollidedWithWall(int offset)
{
	for (auto location : mWallLocations)
	{
		if (mpPlayer->getX() < location[0] + offset &&
			mpPlayer->getX() + offset > location[0] &&
			mpPlayer->getY() < location[1] + offset &&
			mpPlayer->getY() + offset > location[1])
		{
			return true;
		}
	}
	return false;
}

bool UnitManager::playerCollidedWithBody(int offset)
{
	if (mBodyStorage.size() > 20) {
		for (unsigned int i = 0; i  < mBodyStorage.size() - 15 ; i++)
		{
			if (mpPlayer->getX() < mBodyStorage[i]->getX() + offset &&
				mpPlayer->getX() + offset > mBodyStorage[i]->getX() &&
				mpPlayer->getY() < mBodyStorage[i]->getY() + offset &&
				mpPlayer->getY() + offset > mBodyStorage[i]->getY())
			{
				return true;
			}
		}
	}
	return false;
}

bool UnitManager::playerCollidedWithPowerup(Unit* unitName, int offset)
{
	if (mpPlayer->getX() < unitName->getX() + offset &&
		mpPlayer->getX() + offset > unitName->getX() &&
		mpPlayer->getY() < unitName->getY() + offset &&
		mpPlayer->getY() + offset > unitName->getY())
	{
		return true;
	}
	return false;
}

void UnitManager::draw(System* drawingSystem, float scale, int offset) 
{
	for (auto i : mUnitStorage)
	{
		i->draw(drawingSystem, scale, offset);
	}
	for (auto i : mWallStorage)
	{
		i->draw(drawingSystem, scale, offset);
	}
	for (auto i : mUnitStorageNoClear)
	{
		i->draw(drawingSystem, scale, offset);
	}
	for (auto i : mBodyStorage)
	{
		i->draw(drawingSystem, scale, offset);
	}
	if (mpPlayer != nullptr)
	{
		mpPlayer->draw(drawingSystem, scale, offset);
	}
	
}

void UnitManager::clearWallStorage()
{
	for (auto i : mWallStorage)
	{
		delete i;
	}

	for (auto i : mWallLocations)
	{
		delete i;
	}

	mWallStorage.clear();
	mWallLocations.clear();
}

void UnitManager::cleanup() 
{
	if (!mCleanedUp) 
	{
		clearWallStorage();

		for (auto const& i : mUnits)
		{
			delete i.second;
		}

		for (auto i : mUnitStorage)
		{
			delete i;
		}

		for (auto i : mWallLocations)
		{
			delete i;
		}

		for (auto i : mBodyStorage) 
		{
			delete i;
		}

		mCleanedUp = true;
		clear();
	}

}

void UnitManager::clearBodyStorage()
{
	for (auto i : mBodyStorage)
	{
		delete i;
	}

	mBodyStorage.clear();
}

void UnitManager::clear() 
{
	mUnits.clear();
	mAlwaysCreate.clear();
	mUnitStorage.clear();
}

UnitManager::~UnitManager() 
{
	if (!mCleanedUp) 
	{
		cleanup();
	}
}