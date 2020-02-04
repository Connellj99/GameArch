/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Animation.h"

Animation::Animation(double timePerSprite, bool loop)
{
	mCurrentSprite = 0;

	mLoop = loop;

	mTimePerSprite = timePerSprite;
	mTimeLeft = mTimePerSprite;
}
Animation::Animation(Animation* copy)
{
	mCurrentSprite = 0;

	mLoop = copy->mLoop;

	mTimePerSprite = copy->mTimePerSprite;
	mTimeLeft = mTimePerSprite;
	mSprites = copy->mSprites;
}

Animation::~Animation()
{
}

void Animation::addSpriteSheet(GraphicsBuffer* buffer, int rows, int cols)
{
	float sizeX = buffer->getWidth() / cols;
	float sizeY = buffer->getHeight() / rows;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			Sprite sprite(buffer, x * sizeX, y * sizeY, sizeX, sizeY);
			mSprites.push_back(sprite);
		}
	}
}


int Animation::update(double dt)
{
	mTimeLeft -= dt;

	if (mTimeLeft <= 0)
	{
		mTimeLeft = mTimePerSprite;
		if (mCurrentSprite == mSprites.size() - 1)
		{
			mCurrentSprite = 0;
		}
		else
		{
			mCurrentSprite++;
		}
	}
	return 0;
}

Sprite* Animation::currentSprite()
{
	return &(mSprites[mCurrentSprite]);
}


void Animation::adjSpeed(float dt)
{
	
	mTimePerSprite += dt;

	if (mTimePerSprite <= 0)
	{
		mTimePerSprite = 1;
	}
}