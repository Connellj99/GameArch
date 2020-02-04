#include "GamePowerupEvent.h"

GamePowerupEvent::GamePowerupEvent(const PowerupType& pt)
	: Event(GAME_POWERUP_EATEN), ptType(pt)
{
}

GamePowerupEvent::~GamePowerupEvent()
{
}