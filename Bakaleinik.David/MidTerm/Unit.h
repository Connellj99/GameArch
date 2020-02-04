#pragma once
#include <string>
#include "Animation.h"
#include "Trackable.h"

class System;
class Sprite;

class Unit : public Trackable		//A class to hold state information for a game entity – for now, it holds location info for an animation
{

	friend class Game;
protected:

	int mSourceY;
	int mSourceX;

	Animation mUnitAnimation; 

	bool mRunAnimation = true;
	bool mShouldBeDeleted = false;
	
	std::string mObjectType;

public:

	Unit();
	Unit(Animation* startingAnim, int x, int y);
	~Unit();

	std::string getID() { return mObjectType; };

	bool getState() { return mShouldBeDeleted; };
	void changeState() { mShouldBeDeleted = !mShouldBeDeleted; };

	int getXloc() { return mSourceX; };
	int getYloc() { return mSourceY; };

	void setXLoc(int x) { mSourceX = x; };
	void setYLoc(int y) { mSourceY = y; };

	virtual void update(double dTime); //Call Animation's update
	virtual void drawUnit(System *aSystem);
	void setUnitAnimation(Animation* target);
	Animation getUnitAnimation() { return mUnitAnimation; };

	bool isAnimating() { return mRunAnimation; };
	void toggleAnimation() { mRunAnimation = !mRunAnimation; };
	bool checkCollision(int pointerX, int pointerY, int spriteSize);

	//Centipede
	

};