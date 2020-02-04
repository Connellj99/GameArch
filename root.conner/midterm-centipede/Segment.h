/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include "Unit.h"

class Segment : public Trackable
{
private:
	Animation * mpAnim;

	bool mLeft = true;
	bool mHead = false;
	bool mMoveDown = true;

	int mXPos, mYPos;
	int mMaxX, mMaxY;
	int mLastY;

	float mSpeed;

public:
	// Constructor
	Segment(int, int, int, int, int, Animation*);

	// Accessors
	int getXPos() { return mXPos; }
	int getYPos() { return mYPos; }
	bool getIsHead() { return mHead; }
	bool getMovingDown() { return mMoveDown; }

	void setHead() { mHead = true; }
	void setAnimation(Animation* a) { mpAnim = a; }

	void speedUp(float a) { mSpeed += a; }

	// Update
	void update();
	void collide();
	void reset();

	// Draw
	void draw();
};