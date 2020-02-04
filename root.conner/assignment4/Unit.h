/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include "Animation.h"

class Unit : public Trackable
{
private:
	Animation* mpAnim;
	int mXPos, mYPos;

public:
	// Constructor
	Unit();
	Unit(int, int, Animation*);

	// Update
	void setLocation(int, int);
	void update();

	// Accessors
	int getXPos() { return mXPos; }
	int getYPos() { return mYPos; }

	// Draw
	void draw();

	// Animation functions
	Animation* getAnimation() { return mpAnim; }
	void setAnimation(Animation*);

	// Destructor
	~Unit();
};