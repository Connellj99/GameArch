#pragma once
#include "Unit.h"
#include <Trackable.h>
#include <vector>
#include <Vector2D.h>

const int X_BOUND = 30;
const int Y_BOUND = 30;

class UnitManager
{
public:
	UnitManager();
	~UnitManager();

	void update(double time);
	void draw();
	void clear();

	void addUnit(Vector2D location, std::vector<Sprite*> animationList);
	Unit* getUnit();
	
	void removeUnits(Vector2D location);

	void toggleAnimationActive();

private:
	std::vector<Unit*> mpUnitContainer;
	Unit* mpCurrentUnit;

	bool mIsInit;
};

