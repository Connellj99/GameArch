#pragma once

#include "Trackable.h"
#include "Sprite.h"

class Animation : public Trackable		//A class to hold a list of Sprites and the timing information to switch between them
{
private:

	Sprite* mSpriteList[16]; //Smurfs or DeanSprites
	//Timing info
	double mTimeBetweenFrames;
	double mTimeUntilNextFrame;
	int mListIndex;
	Sprite* mpCurrentSprite;
	bool mLoopCheck;


public:

	Animation();
	Animation(GBuffer *spriteSheet, double targetTime, bool loopAnim);
	~Animation();

	void addSprite(Sprite *newSprite);
	void updateAnimation(double dTime);

	Sprite getCurrentSprite() { return *mpCurrentSprite; }; //FIX
	void setCurrentSprite(Sprite *newSprite) { mpCurrentSprite = newSprite; };
	

	void speedUp();
	void slowDown();

};