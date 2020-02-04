/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include "Unit.h"

class Bullet : public Unit
{
private:
	Unit* mpParent;
	Animation* mpAnim;
	int mXPos, mYPos;
	int mSpeed;
	int mMaxYPos;
	bool mActive = false;

public:
	// Constructor
	Bullet();
	Bullet(int, int, int, Animation*, int);
	
	// Bounds check
	bool checkOutOfBounds();

	// Update
	void shoot();
	void reset();
	void update();

	// Accessors
	void setParent(Unit* u) { mpParent = u; }
	bool getActive() { return mActive; }
	int getXPos() { return mXPos; }
	int getYPos() { return mYPos; }

	// Draw
	void draw();
};