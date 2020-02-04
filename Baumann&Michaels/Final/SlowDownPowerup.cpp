#include "SlowDownPowerup.h"
#include "PowerupEvent.h"
#include "EventSystem.h"
SlowDownPowerup::SlowDownPowerup(string newName, Unit* thisNewUnit, double spawnFrequency, UnitManager* newManager)
{
	mName = newName;
	mThisUnit = thisNewUnit;
	mManager = newManager;
	mSpawnFrequency = spawnFrequency;
}

void SlowDownPowerup::onTouchEvent()
{
	EventSystem* fireSystem = EventSystem::getInstance();
	fireSystem->fireEvent(PowerupEvent(PowerupType::SLOW_DOWN));
}