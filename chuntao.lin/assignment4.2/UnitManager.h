#ifndef UNIT_MANAGER_H
#define UNIT_MANAGER_H

// Project-local includes
#include "Unit.h"
#include "Animation.h"
#include "Game.h"

class UnitManager : public Trackable
{
	friend class Game;

public:

	UnitManager();//constructor
	~UnitManager();//destructor

	void cleanUpUnitManager();//clean the unit manager
	void addUnit();//add a new unit to the vector of units
	void removeUnit(int unitIndex);//remove a unit at index

	void clearAllUnits();//clear all units, basically the vector.clear function

	void updateAllUnits();//update units

	void drawAllUnits();//draw units

	//Accessors
	Unit* getUnit(int unitIndex);//return a specific unit

private:
	vector<Unit*> mpListOfUnits;//vector containting all units
	int mNumUnits = 0;//I var I like to use to keep track of units. I know there is just a mpListOfUnits.size(). but I like member vars
};
#endif