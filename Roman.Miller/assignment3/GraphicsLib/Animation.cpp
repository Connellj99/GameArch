#include "Animation.h"


Animation::Animation(GraphicsBuffer &spriteSheet, Vector2D spriteDimensions, double switchTime, bool loopAnimation)
{
	for (auto x = 0; x < spriteSheet.getWidth(); x += spriteDimensions.getX())
	{
		for (auto y = 0; y < spriteSheet.getHeight(); y += spriteDimensions.getY())
		{
			mSpriteVector.push_back(Sprite(&spriteSheet, Vector2D(x, y), spriteDimensions));
		}
	}

	mTargetSwichTime = switchTime;
	mLoop = loopAnimation;
}

Animation::Animation(GraphicsBuffer & spriteSheet, Vector2D spriteDimensions)
{
	for (auto x = 0; x < spriteSheet.getWidth(); x += spriteDimensions.getX())
	{
		for (auto y = 0; y < spriteSheet.getHeight(); y += spriteDimensions.getY())
		{
			mSpriteVector.push_back(Sprite(&spriteSheet, Vector2D(x, y), spriteDimensions));
		}
	}
	mCurrentTime = mTargetSwichTime;
}

Sprite * Animation::getCurrentSprite()
{
	return  &mSpriteVector[mCurrentSprite]; //right kind of pointer?
}

void Animation::speedUp(double time)
{
	mTargetSwichTime -= time;
}

void Animation::slowDown(double time)
{
	mTargetSwichTime += time;
}

void Animation::update(double frameTime)
{
	mCurrentTime -= frameTime;
	if (mCurrentTime <= 0)
	{
		mCurrentSprite++;
		mCurrentSprite = mCurrentSprite % mSpriteVector.size();
		mCurrentTime = mTargetSwichTime;
	}
}

void Animation::updateLocation(Vector2D position)
{
	for (int i = 0; i < mSpriteVector.size(); i++)
	{
		mSpriteVector[i].updateLocation(position);
	}
}
