#ifndef BULLET_UNIT_H
#define BULLET_UNIT_H

#include "Unit.h"

class PlayerUnit;

class BulletUnit : public Unit
{
public:
	BulletUnit();
	~BulletUnit() {}

	void shoot(const Vector2D& initLoc);
	void update(float curTime) override;
private:
	void onCollision(const BoxCollision2D& collision) override;
};
#endif