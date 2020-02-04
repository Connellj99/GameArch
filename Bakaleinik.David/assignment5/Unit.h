#pragma once
#include <string>
#include "Animation.h"
#include "Trackable.h"

class System;

class Unit : public Trackable		//A class to hold state information for a game entity – for now, it holds location info for an animation
{

	friend class Game;
private:

	int mSourceY;
	int mSourceX;

	Animation mUnitAnimation; //Change to be an actual object

	bool mRunAnimation = true;

public:

	Unit();
	Unit(Animation* startingAnim, int x, int y);
	~Unit();

	int getXloc() { return mSourceX; };
	int getYloc() { return mSourceY; };

	void setXLoc(int x) { mSourceX = x; };
	void setYLoc(int y) { mSourceY = y; };

	void update(double dTime); //Call Animation's update
	void drawUnit(System *aSystem);
	void setUnitAnimation(Animation* target);
	Animation getUnitAnimation() { return mUnitAnimation; };

	bool isAnimating() { return mRunAnimation; };
	void toggleAnimation() { mRunAnimation = !mRunAnimation; };
	bool checkCollision(int pointerX, int pointerY, int spriteSize);
};