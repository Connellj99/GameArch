/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include <Timer.h>
#include "Sprite.h"

class Animation : public Trackable
{
private:
	const float SPEED_BASE = 50.0f;
	const float SPEED_CHANGE = 0.025f;
	
	vector<Sprite*> mpSpriteList;
	
	Timer* mpTimer;
	
	float mPrevTime;
	float mSpeed = 0.5f;
	
	int mSpriteIndex;
	
	bool mLoop = true;
	bool mPaused = false;

public:
	// Constructor
	Animation();
	Animation(GraphicsBuffer*, int, int, float, bool);

	// Update
	void update();

	// Speed function
	void speedUp();
	void slowDown();
	void togglePause() { mPaused = !mPaused; }

	// Accessor
	Sprite* getCurrentSprite() { return mpSpriteList[mSpriteIndex]; }

	// Destructor
	~Animation();
};