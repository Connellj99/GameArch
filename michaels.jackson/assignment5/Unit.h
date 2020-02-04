/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef UNIT_H
#define UNIT_H
#include "Animation.h"


class Unit : public Trackable
{
public:
	Unit(int = 0, int = 0);
	~Unit();

	void update(double);

	void draw();

	void setAnimation(Animation* animation) { mAnim = animation; };

	void setLoc(Point pt) { mLoc = pt; };

	Point getLoc() { return mLoc; };

	void toggleAnimate() { mAnimate ? mAnimate = false : mAnimate = true; }

	Animation * getAnimation() { return mAnim; };

private:
	
	bool mAnimate = true;

	Point mLoc;

	Animation * mAnim;


};

#endif // !UNIT_H
