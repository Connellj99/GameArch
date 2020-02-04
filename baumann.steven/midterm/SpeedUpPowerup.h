#pragma once
#ifndef SPEED_UP_POWERUP_H
#define SPEED_UP_POWERUP_H

#include "Powerup.h"
#include <Trackable.h>

class SpeedUpPowerup :public Powerup
{
public:
	SpeedUpPowerup(string newName, Unit* thisNewUnit, double spawnFrequency, UnitManager* newManager);
	void onTouchEvent();

};

#endif