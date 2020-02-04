#ifndef Unit_H
#define Unit_H

#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <time.h> 
#include <vector>

#include "GraphicsSystem.h"

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include "System.h"

class Game;
class Animations;

class Unit : public Trackable
{

public:

	Unit(float xPos, float yPos, std::vector<Animations*> listOfAnims );//constructor
	~Unit();//destructor

	void updateUnitState(float timeAmt,bool speedUp, bool speedDown);//• update – adjusts the state of the Unit – in this case at minimum will call animation’s update function. Takes in the desired time amount

	void drawCurrentAnimation(System* systemObj,bool swap);// draw – draw the current animation’s current sprite in the location of the unit, also to tell if we should swap animations

	//setter
	void setAnimation();//setAnimation – switch to a new animation
	void setUnitScreenStatus(bool unitOn);
	//getter
	bool getUnitScreenStatus() { return mUnitOnScreen; };//function that will return the status of if the unit is on screen

private:

	float mUnitLocationX;
	float mUnitLocationY;
	bool mSwitchAnimations = false;
	
	int mpCurrentAnimationIndex = 0;
	bool mUnitOnScreen = true;

	std::vector<Animations*> mpAnimations;
};
#endif