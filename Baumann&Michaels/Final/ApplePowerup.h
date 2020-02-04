#pragma once
#ifndef APPLE_POWERUP_H
#define APPLE_POWERUP_H

#include "Powerup.h"
#include <Trackable.h>

class ApplePowerup :public Powerup
{
public:
	ApplePowerup(string newName, Unit* thisNewUnit, double spawnFrequency, UnitManager* newManager);
	void onTouchEvent();

};

#endif