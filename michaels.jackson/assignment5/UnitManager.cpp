/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 5
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "UnitManager.h"


UnitManager::UnitManager()
{

}

UnitManager::~UnitManager()
{
	this->clear();
}

int UnitManager::getUnitIndex(Unit* unit)
{
	ptrdiff_t pos = find(mUnits.begin(), mUnits.end(), unit) - mUnits.begin();
	return pos;
}

void UnitManager::addUnit(Unit* unit)
{
	mUnits.push_back(unit);
}

void UnitManager::removeUnit(Unit* unit)
{
	for (std::vector<Unit*>::iterator it = mUnits.begin(); it != mUnits.end(); ++it)
		if (*it == unit)
			delete (*it);

	mUnits.erase(std::remove(mUnits.begin(), mUnits.end(), unit), mUnits.end());
}

void UnitManager::removeUnit(int index)
{
	mUnits.erase(mUnits.begin() + index);
}

Unit* UnitManager::getUnit(int index)
{
	return mUnits.at(index);
}

void UnitManager::clear()
{
	for (std::vector<Unit*>::iterator it = mUnits.begin(); it != mUnits.end(); ++it)
		delete (*it);
	mUnits.clear();
}

void UnitManager::deleteUnitAt(Point target)
{
	for (std::vector<Unit*>::iterator it = mUnits.begin(); it != mUnits.end(); ++it)
	{
		Point loc = (*it)->getLoc();
		if (target.x > loc.x && target.x < loc.x + (*it)->getAnimation()->currentSprite()->getWidth())
			if (target.y > loc.y && target.y < loc.y + (*it)->getAnimation()->currentSprite()->getHeight())
			{
				this->removeUnit(*it);
				break;
			}
	}
}

void UnitManager::update(double dt)
{
	for (std::vector<Unit*>::iterator it = mUnits.begin(); it != mUnits.end(); ++it)
		(*it)->update(dt);
}

void UnitManager::draw()
{
	for (std::vector<Unit*>::iterator it = mUnits.begin(); it != mUnits.end(); ++it)
		(*it)->draw();

}