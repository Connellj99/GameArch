#include "SpeedUpPowerup.h"
#include "PowerupEvent.h"
#include "EventSystem.h"
SpeedUpPowerup::SpeedUpPowerup(string newName, Unit* thisNewUnit, double spawnFrequency, UnitManager* newManager)
{
	mName = newName;
	mThisUnit = thisNewUnit;
	mManager = newManager;
	mSpawnFrequency = spawnFrequency;
}

void SpeedUpPowerup::onTouchEvent()
{
	EventSystem* fireSystem = EventSystem::getInstance();
	fireSystem->fireEvent(PowerupEvent(PowerupType::SPEED_UP));
}