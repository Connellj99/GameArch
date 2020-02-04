#pragma once
#include "Unit.h"
#include <Trackable.h>
#include <vector>
#include <Vector2D.h>
#include <EventListener.h>

const int X_BOUND = 40;
const int Y_BOUND = 40;

class UnitManager : public Trackable
{
public:
	UnitManager();
	~UnitManager();

	void cleanup();
	
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

