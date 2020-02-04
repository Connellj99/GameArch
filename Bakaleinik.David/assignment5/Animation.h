#pragma once

#include "Trackable.h"
#include "Sprite.h"

class Animation : public Trackable		//A class to hold a list of Sprites and the timing information to switch between them
{
private:

	Sprite mSpriteList[16]; //Change to an array of sprites
	//Timing info
	double mTimeBetweenFrames;
	double mTimeUntilNextFrame;
	int mListIndex;
	Sprite* mpCurrentSprite;
	bool mLoopCheck;

	int mID;
	int mArrayCount;
public:

	Animation();
	Animation(GBuffer *spriteSheet, double targetTime, bool loopAnim);
	~Animation();

	void addSprite(Sprite newSprite);
	void updateAnimation(double dTime);

	Sprite* getCurrentSprite() { return mpCurrentSprite; }; 
	void setCurrentSprite(Sprite &newSprite) { mpCurrentSprite = &newSprite; };
	
	int getAnimID() { return mID; };
	void setAnimID(int newID) { mID = newID; };

	void speedUp();
	void slowDown();

};