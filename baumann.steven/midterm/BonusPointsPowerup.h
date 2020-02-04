#pragma once
#ifndef BONUS_POINTS_POWERUP_H
#define BONUS_POINTS_POWERUP_H

#include "Powerup.h"
#include <Trackable.h>

class BonusPointsPowerup :public Powerup
{
public:
	BonusPointsPowerup(string newName, Unit* thisNewUnit, double spawnFrequency, UnitManager* newManager);
	void onTouchEvent();

};

#endif