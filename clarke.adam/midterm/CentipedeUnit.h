#ifndef CENTIPEDE_UNIT_H
#define CENTIPEDE_UNIT_H

#include "Unit.h"

class CentipedeUnit : public Unit
{
public:
	CentipedeUnit();
	~CentipedeUnit();

	void respawn(float speedIncrement, const Vector2D& loc);
	void update(float curTime) override;
	void onCollision(const BoxCollision2D& collision) override;
private:
	CentipedeUnit* mHead = nullptr;
	CentipedeUnit* mTail = nullptr;

	float mInitMoveSpeed = 0;
	float mMoveSpeed = 0;
	Vector2D mMoveDir = Vector2D(1, 1);
	Vector2D mTarLoc = Vector2D(0, 0);

	bool doIgnoreNextMushroom = false;
	BoxCollider2D* mIgnoredMushroom = nullptr;

	void increaseSpeedHead();
	void increaseSpeedTail();
	void dropSwap();
	void checkWallCollision();
	void move();
	void removeSelf();
	void ignoreNextMushroom();

	friend class CentipedeManager;
};
#endif