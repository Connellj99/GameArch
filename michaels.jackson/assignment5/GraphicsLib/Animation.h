/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#pragma once
#include "Sprite.h"
#include <vector>

class Animation : public Trackable
{
public:
	Animation(double, bool = true);
	Animation(Animation*);
	~Animation();

	void addSprite(Sprite input) { mSprites.push_back(input); };
	void addSpriteSheet(GraphicsBuffer* buffer, int rows, int cols);


	int update(double);
	Sprite* currentSprite();
	void adjSpeed(float);


private:
	std::vector<Sprite> mSprites;
	int mCurrentSprite;
	bool mLoop;

	double mTimePerSprite;
	double mTimeLeft;

};