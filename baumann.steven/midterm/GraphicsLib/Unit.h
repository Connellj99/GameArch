#pragma once
#pragma once

#ifndef UNIT_H
#define UNIT_H

#include "Trackable.h"
#include "Animation.h"
#include "System.h"
#include <vector>


using namespace std;

class Unit :public Trackable
{
private:
	vector<Animation*> mAnimationSheet;
	int mCurrentX;
	int mCurrentY;
	int mCurrentAnimation;
	int mTotalAnimations;
	int mCurrentSpeed;
	int mDefaultSpeed;
	int mCurrentSprite;
	double mLastTime;
	bool mIsCopy = false;
	bool mIsFrozen = false;
public:
	Unit();
	Unit(Unit* copy, int* coords);
	~Unit();
	void update(double elapsedTime); //Used to call Animation's update function.
	int getX();
	int getY();
	void draw(System* drawSystem, float offset, float scale);
	void setAnimation(int animNum); //Set new animation.
	void incrementAnimation();
	void swapFrozen();
	void speedUp();
	void slowDown();
	void addAnimation(Animation* anim);
	Animation* getAnimation();
	void updateLocation(int x, int y);
};

#endif