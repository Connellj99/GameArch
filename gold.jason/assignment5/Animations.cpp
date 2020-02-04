#include "Animations.h"

Animations::Animations(std::vector<Sprites*> animVector)
{
	mAnimationVector = animVector;
	mCurrentSprite = 0;
	mVectorMax = animVector.size();
	mLooping = true;
	mTimeInfo = 100.0;
	mTimeUntilFrame = 100.0;
}

Animations::~Animations()
{
	
}

void Animations::Update(double time)
{
	mTimeInfo -= time;
	if(mTimeInfo <= 0.0)
	{
		if(mLooping)
		{
			mCurrentSprite++;
			if(mCurrentSprite >= mVectorMax)
			{
				mCurrentSprite = 0;
			}
		}
		mTimeInfo = mTimeUntilFrame;
	}
}

void Animations::switchLooping()
{
	mLooping = !mLooping;
}

void Animations::SlowDown(double adjustment)
{
	mTimeUntilFrame -= adjustment;
}

void Animations::SpeedUp(double adjustment)
{
	mTimeUntilFrame += adjustment;
}

Sprites* Animations::getCurrentSprite()
{
	return mAnimationVector[mCurrentSprite];
}