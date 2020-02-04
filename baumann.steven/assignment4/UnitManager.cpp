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

void UnitManager::addToStorage(string unitName) 
{
	mUnitStorage.push_back(getUnit(unitName));
}

void UnitManager::addToStorage(Unit* unit) 
{
	mUnitStorage.push_back(unit);
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

void UnitManager::update(double elapsedTime)
{
	for (auto i : mUnitStorage)
	{
		i->update(elapsedTime);
	}
}

void UnitManager::draw(System* drawingSystem, float scale, int offset) 
{
	for (auto i : mUnitStorage)
	{
		i->draw(drawingSystem, scale, offset);
	}
}

void UnitManager::cleanup() 
{
	if (!mCleanedUp) 
	{
		for (auto const& i : mUnits)
		{
			delete i.second;
		}

		for (auto i : mUnitStorage)
		{
			delete i;
		}

		mCleanedUp = true;
	}

}

void UnitManager::clear() 
{
	mUnits.clear();
}

UnitManager::~UnitManager() 
{
	if (!mCleanedUp) 
	{
		cleanup();
	}
}