#include "Unit.h"

Unit::Unit() 
{
	mCurrentX = 100;
	mCurrentY = 100;
	mCurrentSpeed = 0.3;
	mDefaultSpeed = 0;
	mCurrentAnimation = 0;
	mCurrentSprite = 0;
	mTotalAnimations = 0;
	mLastTime = 0;
}

Unit::Unit(Unit* copy, int* coords)
{
	mCurrentX = coords[0];
	mCurrentY = coords[1];
	mCurrentAnimation = 0;
	mCurrentSpeed = 0.3;
	mDefaultSpeed = mCurrentSpeed;
	mCurrentSprite = 0;
	mTotalAnimations = copy->mTotalAnimations;
	mAnimationSheet = copy->mAnimationSheet;
	mIsCopy = true;
}

int Unit::getX() 
{
	return mCurrentX;
}

int Unit::getY() 
{
	return mCurrentY;
}

void Unit::draw(System* drawSystem, float scale, float offset)
{
	Sprite* newSprite = getAnimation()->getSprite(mCurrentSprite);
	drawSystem->draw(mCurrentX - offset, mCurrentY - offset, newSprite, scale);
}

void Unit::swapFrozen() 
{
	mIsFrozen = !mIsFrozen;
}

void Unit::update(double elapsedTime) 
{
	if (elapsedTime > mCurrentSpeed) 
	{
		if (!mIsFrozen) 
		{
			mCurrentSprite++;
		}
		if (mCurrentSprite == mAnimationSheet[mCurrentAnimation]->getTotalSprites()) 
		{
			mCurrentSprite = 0;
		}
		mCurrentSpeed += mDefaultSpeed;
	}
}

void Unit::updateLocation(int x, int y) 
{
	mCurrentX = x;
	mCurrentY = y;
}

void Unit::setAnimation(int animNum) 
{
	mCurrentAnimation = animNum;
}

void Unit::speedUp()
{
	mCurrentSpeed += mDefaultSpeed;
}

void Unit::slowDown()
{
	if (mCurrentSpeed - mDefaultSpeed != 0)
	{
		mCurrentSpeed -= mDefaultSpeed;
	}
}

void Unit::incrementAnimation() 
{
	if (mCurrentAnimation == mTotalAnimations - 1) 
	{
		mCurrentAnimation = 0;
	}
	else {
		mCurrentAnimation++;
	}
}

void Unit::addAnimation(Animation* anim) 
{
	mAnimationSheet.push_back(anim);
	mTotalAnimations++;
}

Animation* Unit::getAnimation() 
{
	return mAnimationSheet[mCurrentAnimation];
}
Unit::~Unit() 
{
	if (!mIsCopy) 
	{
		for (auto i : mAnimationSheet)
		{
			delete i;
		}
	}
	
}