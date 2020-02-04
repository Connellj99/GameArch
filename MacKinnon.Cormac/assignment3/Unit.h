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
#include "Game.h"

class Animation;

class Unit : public Trackable
{
public:
	Unit();
	Unit(Vector2D unitLocation);
	~Unit();
	//updates the unit
	void update();

	void draw();
	//sets the animation to active one
	void setAnimation();
	//adds animation to vector of animations
	void addAnimation(Animation* animation);
	//sets unit location
	void setUnitLocation(Vector2D unitLocation);
	//checks to see if unit is visible
	bool isVisible();

private:
	Animation* getCurrentAnimation();

	Vector2D mUnitLocation;
	std::vector<Animation*> mpAnimationsList;
	int mCurrentIndexPos;
};
#endif // !UNIT_H
