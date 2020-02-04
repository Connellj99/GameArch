/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include "System.h"

class Unit : public Trackable
{
public:
	Unit(int = 0, int = 0);
	~Unit();

	void update(double);

	void draw();

	void setAnimation(Animation* animation) { mAnim = animation; };

	void setLoc(Point pt) { mLoc = pt; };

	Animation * getAnimation() { return mAnim; };

private:
	
	Point mLoc;

	Animation * mAnim;


};