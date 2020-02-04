#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>
#include "Vector2D.h"
#include <vector>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include "Animation.h"
//#include "Game.h"

class Animation;

class Unit : public Trackable
{
public:
	Unit();
	Unit(Vector2D unitLocation, std::vector<Sprite*> animationList);
	~Unit();
	//updates the unit
	void update(double time);

	void draw();
	//sets the animation to active one
	void setAnimation();
	//adds animation to vector of animations
	void addAnimation(Animation* animation);
	void addAnimation(std::vector<Sprite*> animationList);
	//sets unit location
	void setUnitLocation(Vector2D unitLocation);
	//checks to see if unit is visible
	bool isVisible();

	Vector2D getLocation();
	int getUnitLocX();
	int getUnitLocY();
	Animation* getCurrentAnimation();

private:
	
	Vector2D mUnitLocation;
	std::vector<Animation*> mpAnimationsList;
	int mCurrentIndexPos;
	Animation* mpCurrentAnim;
	Timer* mpTimer;
};
#endif // !UNIT_H
