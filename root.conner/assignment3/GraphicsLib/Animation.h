/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include <vector>
#include <Timer.h>
#include "Sprite.h"

class Animation : public Trackable
{
private:
	const float SPEED_CHANGE = 160.0f;
	
	vector<Sprite*> mpSpriteList;
	
	Timer* mpTimer;
	
	float mPrevTime;
	float mSpeed = 16.0;
	
	int mSpriteIndex;
	
	bool mLoop = true;

public:
	// Constructor
	Animation();
	Animation(GraphicsBuffer*, int, int, float, bool);

	// Update
	void update();

	// Speed function
	void speedUp();
	void slowDown();

	// Accessor
	Sprite* getCurrentSprite() { return mpSpriteList[mSpriteIndex]; }

	// Destructor
	~Animation();
};