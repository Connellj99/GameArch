/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include <PerformanceTracker.h>

#include "Unit.h"
#include "Bullet.h"
#include "Segment.h"

class Game;

class UnitManager : public Trackable
{
private:
	int mDispW, mDispH;
	float mBaseCentSpeed = 3;
	float mSpeedIncrease;

	Animation* mpPlayerAnim = nullptr;
	Animation* mpMushroomAnim = nullptr;
	Animation* mpBulletAnim = nullptr;
	Animation* mpCentipedeHeadAnim = nullptr;
	Animation* mpCentipedeBodyAnim = nullptr;
	
	Unit* mpPlayer = nullptr;
	Bullet* mpBullet = nullptr;
	vector<Unit*> mpMushroomList;
	vector<Segment*> mpCentipede;

	// Add units
	void generateMushrooms();
	void generateCentipede();
	void addMushroom(int, int);

public:
	// Constructor
	UnitManager();

	// Init
	void init();
	void init(int, int);
	void setUnits();

	// Add animation
	void addAnim(GraphicsBuffer*, int, int, float, bool);

	// Accessor
	void shoot() { mpBullet->shoot(); }
	Unit* getPlayer() { return mpPlayer; }
	Unit* getUnit();

	// Other Functions
	void speedUpCentipede(float);
	void increaseDifficulty(float);
	void resetAllUnitStates();	// For Ended Game

	// Update
	void updateUnits();
	void drawUnits();

	// Find collisions
	void detectSegmentCollision();

	// Delete units
	void deleteUnit(int, int);
	void deleteAllUnits();

	// Destructor
	~UnitManager();
};