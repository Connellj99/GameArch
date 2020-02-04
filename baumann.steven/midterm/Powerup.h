#pragma once
#ifndef POWERUP_H
#define POWERUP_H

#include "UnitManager.h"
#include <string>
#include <Trackable.h>

using namespace std;

class Powerup :public Trackable
{
protected:
	string mName;
	UnitManager* mManager;
	Unit* mThisUnit;
	double mSpawnFrequency;
	Powerup() {};

public:
	
	Powerup(string newName, Unit* thisNewUnit, double spawnFrequency, UnitManager* newManager);
	Unit* getThisUnit();

	string getName() { return mName; }
	double getSpawnFrequency() { return mSpawnFrequency; }
	virtual void onTouchEvent() {};

};

#endif