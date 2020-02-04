#include "Unit.h"

Unit::Unit() {
	mCurrentX = 0;
	mCurrentY = 0;
	mCurrentAnimation = 0;
	mTotalAnimations = 0;
}

void Unit::update() {
	mAnimationSheet[mCurrentAnimation]->update();
}

void Unit::updateLocation(int x, int y) {
	mCurrentX = x;
	mCurrentY = y;
}

void Unit::setAnimation(int animNum) {
	mCurrentAnimation = animNum;
}

void Unit::incrementAnimation() {
	if (mCurrentAnimation == mTotalAnimations - 1) {
		mCurrentAnimation = 0;
	}
	else {
		mCurrentAnimation++;
	}
}

void Unit::addAnimation(Animation* anim) {
	mAnimationSheet.push_back(anim);
	mTotalAnimations++;
}

Animation* Unit::getAnimation() {
	return mAnimationSheet[mCurrentAnimation];
}
Unit::~Unit() {
	for (auto i : mAnimationSheet) {
		delete i;
	}
}