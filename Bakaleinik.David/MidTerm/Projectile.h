#pragma once
#include "Unit.h"

class System;
class Sprite;

class Projectile : public Unit
{
public:

	Projectile(Sprite* sprite, int x, int y);
	~Projectile() {};

	void drawUnit(System* aSystem);

	/*int getPosX() { return mPosX; };
	int getPosY() { return mPosY; };

	void setPosX(int newX) { mPosX = newX; };
	void setPosY(int newY) { mPosY = newY; };*/

	void update(double time);

private:

	//int mPosX;
	//int mPosY;

	Sprite mBullet;
};