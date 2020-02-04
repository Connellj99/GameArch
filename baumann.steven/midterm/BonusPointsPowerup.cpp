#include "BonusPointsPowerup.h"
#include "PowerupEvent.h"
#include "EventSystem.h"
BonusPointsPowerup::BonusPointsPowerup(string newName, Unit* thisNewUnit, double spawnFrequency, UnitManager* newManager)
{
	mName = newName;
	mThisUnit = thisNewUnit;
	mManager = newManager;
	mSpawnFrequency = spawnFrequency;
}

void BonusPointsPowerup::onTouchEvent()
{
	EventSystem* fireSystem = EventSystem::getInstance();
	fireSystem->fireEvent(PowerupEvent(PowerupType::BONUS_POINTS));
}