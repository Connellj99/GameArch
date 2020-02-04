/*
Author: Steven Pershyn
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is my own work, except where I referenced classmates' work and mentioned where relevant.
*/
#pragma once
#include "GraphicsSystem.h"
#include <vector>
class Animation: public Trackable
{
public:
	Animation(double, bool = true);
	~Animation();

	void addSprite(Sprite input) { mSprites.push_back(input); };
	void addSpriteSheet(GraphicsBuffer* buffer, int rows, int cols);


	int update(double);
	Sprite* currentSprite();
	void adjSpeed(float);
private:
	vector<Sprite> mSprites;
	int mCurrentSprite;
	bool mLoop;

	double mTimePerSprite;
	double mTimeLeft;
};