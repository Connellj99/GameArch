#ifndef PLAYER_UNIT_H
#define PLAYER_UNIT_H

#include "Unit.h."

class PlayerUnit : public Unit
{
public:
	PlayerUnit(std::map<std::string, Animation>& animations, const Vector2D& initLoc, const Vector2D& scale);
	~PlayerUnit();

	void handleEvent(const Event& theEvent) override;

	void update(float curTime) override;

private:
	int mXMovDir = 1;
	float mMoveSpeed = 10.0f;
};
#endif