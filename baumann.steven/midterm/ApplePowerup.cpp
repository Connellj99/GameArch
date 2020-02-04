#include "ApplePowerup.h"
#include "PowerupEvent.h"
#include "EventSystem.h"
ApplePowerup::ApplePowerup(string newName, Unit* thisNewUnit, double spawnFrequency, UnitManager* newManager)
{
	mName = newName;
	mThisUnit = thisNewUnit;
	mManager = newManager;
	mSpawnFrequency = spawnFrequency;
}

void ApplePowerup::onTouchEvent()
{
	EventSystem* fireSystem = EventSystem::getInstance();
	fireSystem->fireEvent(PowerupEvent(PowerupType::APPLE_EATEN));
}