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
	friend class Unit;
private:
	//List of sprites (vector)
	vector<Sprite*> mvSpriteList;

	//Timing info
	double targetTime = 100.0;
	double dT = 16.7;
	int animationIndex = 0;

	//Index of current sprite in the vector
	int mCurrentSprite;

	//Loop animation?
	bool mShouldLoop;

public:
	//constructor
	Animation();

	//destructor
	~Animation();

	//add sprites to animation
	void addSprite(GraphicsBuffer * pBuffer, int size);

	//Update - figure out current sprite
	void update();

	//getCurrentSprite
	Sprite * getCurrentSprite();

	//speed up/slow down
	void changeSpeed(double value);
};