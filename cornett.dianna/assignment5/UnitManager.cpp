/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/


#include "UnitManager.h"

/*
Create unitManager and set mIsInit to true
*/
UnitManager::UnitManager()
{
	mIsInit = true;
}

/*
Destroy the unit manager if it has been inited
*/
UnitManager::~UnitManager()
{
	if (mIsInit)
	{
		clear();
		mIsInit = false;
	}
	
}

/*
Add a new unit to the end of the list
*/
void UnitManager::add(Unit * unit)
{
	mUnits.push_back(unit);
}

/*
Remove all units from the list and delete them. Sets isInit to false so things aren't deleted twice
*/
void UnitManager::clear()
{
	mIsInit = false;

	for (Unit * unit : mUnits) 
	{
		if (unit != NULL)
		{
			delete unit;
		}
	}
}

/*
Call Update on each unit in the list of units
*/
void UnitManager::update(double deltaTime)
{
	for (Unit * unit : mUnits)
	{
		//Takes time in secounds so units must be converted
		unit->update(deltaTime);
	}
}

/*
Draw each unit to the screen. Takes a pointer to the system
*/
void UnitManager::draw(System * system)
{
	for (Unit * unit : mUnits)
	{
		unit->draw(system);
	}
}

/*
Get the last unit in the list
*/
Unit* UnitManager::getLastUnit() 
{
	return mUnits.back();
}

/*
Set if a given unit should animate
*/
void UnitManager::setIsAnimating(bool isAnimating)
{
	for (Unit * unit : mUnits)
	{
		unit->setIsAnimating(isAnimating);
	}
}


/*
Delete all units at a position pos
*/
void UnitManager::deleteAtPosition(Position pos)
{

	//Add all units that should be deleted to a vector
	std::vector<Unit*> toDelete;
	for (Unit * unit : mUnits)
	{
		if (unit->positionIsInUnit(pos))
		{
			toDelete.push_back(unit);
		}
	}
	
	//Remove the units from the list
	mUnits.remove_if([pos](Unit * unit) 
	{
		return unit->positionIsInUnit(pos);
	});

	//Deallocate the memory of the deleted units
	for (Unit * unit : toDelete) 
	{
		delete unit;
		unit = NULL;
	}

}