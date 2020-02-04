#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Trackable.h"
#include "Sprite.h"
#include <vector>

using namespace std;

class Animation : public Trackable
{
private:
	//List of sprites (vector)
	vector<Sprite*> mvSpriteList;

	//Timing info
	double mTargetTime = 100.0;
	int mAnimationIndex = 0;
	double mTimeBetweenFrames;

	//Index of current sprite in the vector
	int mCurrentSprite;

	//Loop animation?
	bool mShouldLoop = true;

public:
	//constructor
	Animation();

	//destructor
	~Animation();

	//add sprites to animation
	void addSprite(GraphicsBuffer * pBuffer, int size);

	//Update - figure out current sprite
	void update(double dT);

	//getCurrentSprite
	Sprite * getCurrentSprite();

	//speed up/slow down
	void changeSpeed(double value);

	//toggle animation
	void toggleAnim();
};