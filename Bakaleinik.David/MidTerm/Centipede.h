#pragma once
#include <vector>
#include "Unit.h"

class Sprite;
class Animation;
class System;

class Centipede : public Unit
{
public:

	Centipede(Sprite* image, int x, int y, int speed);
	~Centipede() {};

	int getMoveSpeed() { return mMoveSpeed; };
	void setMoveSpeed(int newSpeed) { mMoveSpeed = newSpeed; };
	void increaseSpeedByAmount(int newSpeed) { mMoveSpeed += newSpeed; };
	void update(double dTime);
	void drawUnit(System* aSystem);

	void changeDirection() { mShouldTurn = !mShouldTurn; };
	void dropDown() { mSourceY += 10; };
	void partialReset() { mSourceY -= 400; };

private:
	
	bool mShouldTurn = false;
	int mMoveSpeed;
	Sprite* mpBodySegment;
};