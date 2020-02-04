#pragma once
#pragma once

#ifndef UNIT_H
#define UNIT_H

#include "Trackable.h"
#include "Animation.h"
#include <vector>
#include <allegro5/allegro.h>


using namespace std;

class Unit :public Trackable
{
private:
	vector<Animation*> mAnimationSheet;
	int mCurrentX;
	int mCurrentY;
	int mCurrentAnimation;
	int mTotalAnimations;
public:
	Unit();
	~Unit();
	void update(); //Used to call Animation's update function.
	void setAnimation(int animNum); //Set new animation.
	void incrementAnimation();
	void addAnimation(Animation* anim);
	Animation* getAnimation();
	void updateLocation(int x, int y);
};

#endif