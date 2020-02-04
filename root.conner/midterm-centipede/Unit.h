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
	int mHP = 4;

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
	int getHealth() { return mHP; }

	void getHit() { mHP--; }

	// Draw
	void draw();

	// Animation functions
	Animation* getAnimation() { return mpAnim; }
	void setAnimation(Animation*);

	// Destructor
	~Unit();
};