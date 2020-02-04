#include "UnitManager.h"

UnitManager::UnitManager()
{

}

UnitManager::~UnitManager()
{
	cleanup();
}

void UnitManager::init()
{

}

void UnitManager::cleanup()
{
	for (int i = 0; i < mUnitList.size(); i++)
	{
		delete mUnitList[i];
	}
	removeAllUnits();
}

void UnitManager::addNewUnit(GraphicsBuffer* spriteMap, int rows, int columns)
{
	Unit* newUnit = new Unit();
	newUnit->loadAnimation(spriteMap, rows, columns);
	mUnitList.push_back(newUnit);
}

void UnitManager::addUnit(Unit* unit)
{
	mUnitList.push_back(unit);
}

Unit* UnitManager::getUnit(int index)
{

	if (index < mUnitList.size())
	{
		return mUnitList[index];
	}
	return nullptr;
}

int UnitManager::getSize()
{
	return mUnitList.size();
}

void UnitManager::removeUnit(int index)
{
	if (index < mUnitList.size() && index >= 0)
	{
		delete mUnitList[index];
		std::vector<Unit*>::iterator it = mUnitList.begin();
		std::advance(it, index);
		mUnitList.erase(it);
	}
}

void UnitManager::removeAllUnits()
{
	mUnitList.clear();
}

void UnitManager::removeSpecificUnit(Unit* type)
{
	removeUnit(findIndex(type));
}

void UnitManager::removeUnitsAt(float x, float y)
{
	for (int i = 0; i < mUnitList.size(); i++)
	{
		if (mUnitList[i]->getX() <= x + mUnitList[i]->getWidth() / 2.0 && mUnitList[i]->getX() > x - mUnitList[i]->getWidth()/2.0) //Makes use of short-circuiting to allow for quickly parsing through long lists of units
		{
			if (mUnitList[i]->getY() <= y + mUnitList[i]->getHeight() / 2.0 && mUnitList[i]->getY() > y - mUnitList[i]->getHeight()/2.0)
			{
				removeSpecificUnit(mUnitList[i]);
			}
		}
	}
}

void UnitManager::update()
{
	for (int i = 0; i < mUnitList.size(); i++)
	{
		mUnitList[i]->update();
	}
}

void UnitManager::draw()
{
	for (int i = 0; i < mUnitList.size(); i++)
	{
		mUnitList[i]->draw();
	}
}

int UnitManager::findIndex(Unit* unit)
{
	for (int i = 0; i < mUnitList.size(); i++)
	{
		if (mUnitList[i] == unit)
		{
			return i;
		}
	}

	return -1;
}

void UnitManager::setX(float x, int index)
{
	if (index < mUnitList.size() && index >= 0)
	{
		mUnitList[index]->setX(x);
	}
}

void UnitManager::setY(float y, int index)
{
	if (index < mUnitList.size() && index >= 0)
	{
		mUnitList[index]->setY(y);
	}
}

float UnitManager::getX(int index)
{
	if (index < mUnitList.size() && index >= 0)
	{
		return mUnitList[index]->getX();
	}

	return -1;
}

float UnitManager::getY(int index)
{
	if (index < mUnitList.size() && index >= 0)
	{
		return mUnitList[index]->getY();
	}

	return -1;
}