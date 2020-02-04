/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include <PerformanceTracker.h>

#include "Unit.h"

class Game;

class UnitManager : public Trackable
{
private:
	bool mAnimDean = false;

	Animation* mpAnim1 = nullptr;
	Animation* mpAnim2 = nullptr;

	vector<Unit*> mpCharacterList;

public:
	// Constructor
	UnitManager();
	UnitManager(Animation*, Animation*);

	// Add animation
	void addAnim(GraphicsBuffer*, int, int, float, bool);

	// Add units
	void addUnit(int, int);

	// Accessor
	Unit* getUnit();

	// Other functions
	void switchAnimation();
	void toggleAnimationPause();
	void updateUnits();
	void drawUnits();

	// Delete units
	void deleteUnit(int, int);
	void deleteAllUnits();

	// Destructor
	~UnitManager();
};