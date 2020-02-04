#include "UnitManager.h"

UnitManager::UnitManager()
{
}

UnitManager::~UnitManager()
{
	cleanUpUnitManager();//call the clean game manager function
}

void UnitManager::cleanUpUnitManager()
{
		if (mNumUnits > 0)//if its time to cleanup and there are still units on screen. then remove, starting with first unit. First unit deleted will also remove the vector of sprites further on.
		{
			mpListOfUnits[0]->cleanUnitAndSprites();	
		}

	for (Unit* units : mpListOfUnits)//any left over units this will clear just in case. This will remove the animations on all units
	{
		delete units;
	}

}

void UnitManager::addUnit()
{
	mpListOfUnits.push_back(new Unit);//push a new unit and add to the counter that I have
	mNumUnits++;
}

void UnitManager::removeUnit(int unitIndex)
{
	if (mpListOfUnits[unitIndex] != NULL)//if the index is not null
	{
		if (mNumUnits == 1)//if the last unit is going to be deleted
		{
			for (Unit* units : mpListOfUnits)//then delete the units if albe
			{
				delete units;
			}
			mpListOfUnits.erase(mpListOfUnits.begin() + unitIndex);//delete from the index again just to be sure.
			mNumUnits--;//deduct from the counter
		}
		else
		{
			delete mpListOfUnits[unitIndex];//delete from index, to clear any DAM(dynamic allocated memory
			mpListOfUnits.erase(mpListOfUnits.begin() + unitIndex);//delete from index in the vector, therefore making size smaller
			mNumUnits--;//deduct from the counter
		}
	}
}

Unit* UnitManager::getUnit(int unitIndex)
{
	return mpListOfUnits[unitIndex];//return the unit at indicated index
}

void UnitManager::clearAllUnits()
{
	mpListOfUnits.clear();//clear the entire vector of units
}

void UnitManager::updateAllUnits()
{
	for (Unit* unit : mpListOfUnits)//update all of the units
	{
		unit->update(MAX_TIME_BETWEEN_FRAMES);
	}
}

void UnitManager::drawAllUnits()
{
	for (Unit* unit : mpListOfUnits)//for all units, draw the units with their location and sprite
	{
		Game::getInstance()->getCurrentSystem()->getGraphicsSystem().draw(unit->returnLocation(),*unit->getCurrentAnimation()->getCurrentSprite(), DEFAULT_SCALING_VALUE);
	}
}
