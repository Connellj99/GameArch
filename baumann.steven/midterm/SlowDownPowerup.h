#pragma once
#ifndef SLOW_DOWN_POWERUP_H
#define SLOW_DOWN_POWERUP_H

#include "Powerup.h"
#include <Trackable.h>

class SlowDownPowerup :public Powerup
{
public:
	SlowDownPowerup(string newName, Unit* thisNewUnit, double spawnFrequency, UnitManager* newManager);
	void onTouchEvent();

};

#endif