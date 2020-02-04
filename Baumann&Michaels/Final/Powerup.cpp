#include "Powerup.h"

Powerup::Powerup(string newName, Unit* thisNewUnit, double spawnFrequency,  UnitManager* newManager)
{ 
	mName = newName; 
	mThisUnit = thisNewUnit;
	mManager = newManager;
	mSpawnFrequency = spawnFrequency;
}

Unit* Powerup::getThisUnit() 
{ 
	return mThisUnit; 
}