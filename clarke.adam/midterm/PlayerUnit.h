#ifndef PLAYER_UNIT_H
#define PLAYER_UNIT_H

#include "Unit.h"
#include "EventListener.h"
#include "GraphicsBufferManager.h"
#include "BoxCollider2D.h"
#include "BulletUnit.h"

class MushroomUnitManager;

class PlayerUnit : public Unit, EventListener
{
public:
	PlayerUnit();
	~PlayerUnit();
	void cleanup() override;
	void physicsUpdate(float curTime) override;
	void update(float curTime) override;
	void draw() const override;
	void respawn();
private:
	void handleEvent(const Event& theEvent) override;
	void onCollision(const BoxCollision2D& collision) override;
	void playerMove(const Vector2D& tarLoc);
	void playerShoot();

	Vector2D mMinPlayerLoc = (0, 0);
	Vector2D mMaxPlayerLoc = (0, 0);

	Vector2D mTarLoc;

	BulletUnit* mpBulletUnit;

	bool mIsShooting = false;
};
#endif
