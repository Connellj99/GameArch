/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Animation.h"

Animation::Animation()
{
	
}

Animation::~Animation()
{
	int listSize = mvSpriteList.size();
	for (int i = 0; i < listSize; i++)
	{
		delete mvSpriteList[i];
	}
	mvSpriteList.clear();
}

void Animation::update(double dT)
{
	if (mShouldLoop)
	{
		mTimeBetweenFrames -= dT;

		if (mTimeBetweenFrames <= 0)
		{
			mCurrentSprite = mAnimationIndex;
			mAnimationIndex++;

			if (mAnimationIndex == mvSpriteList.size() - 1)
			{
				mAnimationIndex = 0;
			}
			mTimeBetweenFrames = mTargetTime;
		}
	}
}

void Animation::addSprite(GraphicsBuffer * pBuffer, int size)
{
	int spriteX = pBuffer->getBitmapWidth() / size;
	int spriteY = pBuffer->getBitmapHeight() / size;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			mvSpriteList.push_back(new Sprite((i * spriteX), (j * spriteY), spriteX, spriteY, pBuffer));
		}
	}
}

void Animation::changeSpeed(double value)
{
	mTargetTime += value;
}

Sprite * Animation::getCurrentSprite()
{
	return mvSpriteList[mCurrentSprite];
}

void Animation::toggleAnim()
{
	if (mShouldLoop)
	{
		mShouldLoop = false;
	}
	else
	{
		mShouldLoop = true;
	}
}