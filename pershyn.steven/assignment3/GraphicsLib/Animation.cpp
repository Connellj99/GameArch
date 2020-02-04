/*
Author: Steven Pershyn
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is my own work, except where I referenced classmates' work and mentioned where relevant.
*/
#include "Animation.h"

Animation::Animation(double timePerSprite, bool loop)
{
	mCurrentSprite = 0;

	mLoop = loop;

	mTimePerSprite = timePerSprite;
	mTimeLeft = mTimePerSprite;
}

Animation::~Animation()
{

}

void Animation::addSpriteSheet(GraphicsBuffer* buffer, int rows, int cols)
{
	float sizeX = buffer->getWidth() / cols;
	float sizeY = buffer->getHeight() / rows;

	for (int x = 0; x < cols; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			Sprite sprite(x * sizeX, y * sizeY, sizeX, sizeY, buffer);
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