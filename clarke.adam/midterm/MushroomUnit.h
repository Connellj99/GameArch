#ifndef MUSHROOM_UNIT_H
#define MUSHROOM_UNIT_H

#include "Unit.h"

class MushroomUnit : public Unit
{
	MushroomUnit(const Vector2D& initLoc);
	~MushroomUnit() {}

	void onCollision(const BoxCollision2D& collision) override;

	unsigned int mHitPoints = 0;

	friend class MushroomUnitManager;
};
#endif