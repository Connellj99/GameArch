#pragma once
#ifndef GAME_POWERUP_EVENT_H
#define GAME_POWERUP_EVENT_H

#include "PowerupEvent.h"

class GamePowerupEvent :public Event
{
private:
	PowerupType ptType;

public:


	GamePowerupEvent(const PowerupType& mb);
	~GamePowerupEvent();

	PowerupType getButtonType() const { return ptType; }
};

#endif