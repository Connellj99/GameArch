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
	for (int i = 0; i < mvSpriteList.size(); i++)
	{
		delete mvSpriteList[i];
	}
	mvSpriteList.clear();
}

void Animation::update()
{
	double timeBetweenFrames = targetTime;
	timeBetweenFrames -= dT;

	if (timeBetweenFrames <= 0)
	{
		mCurrentSprite = animationIndex;
		animationIndex++;

		if (animationIndex == mvSpriteList.size() - 1)
		{
			animationIndex = 0;
		}
		timeBetweenFrames = targetTime;
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
	targetTime += value;
}

Sprite * Animation::getCurrentSprite()
{
	return mvSpriteList[mCurrentSprite];
}