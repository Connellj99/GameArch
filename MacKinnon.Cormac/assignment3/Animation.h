#pragma once

#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>
#include <vector>

#include "System.h"

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

class Sprite;
class GraphicsBuffer;

class Animation : public Trackable
{
public:
	Animation(GraphicsBuffer* pSpriteSheet, int spriteWidth, int spriteHeight, int numSpriteX, int numSpriteY, bool animate);
	~Animation();
	//adds sprite to vector of sprites
	void addSprites(Sprite* sprite);
	//updates the current sprite or animation
	void update();
	//accessor for current sprite
	Sprite* getCurrentSprite();

	//speed of animation adjustres
	void speedUpAnimation();
	void speedDownAnimation();

private:
	bool mAnimate;

	std::vector<Sprite*> mpListOfSprites;
	Sprite* mpCurrentSprite;
	Timer* mpAnimationTimer;

	int mCurrentSprite;
	int mTotalSprites;

	double mTiming;
	double mPreviousFrameTime;
	double mCurrentFrameTime;
};

