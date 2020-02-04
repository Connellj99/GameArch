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

	// Draw
	void draw();

	// Switch to a new animation
	void setAnimation(Animation*);

	// Destructor
	~Unit();
};