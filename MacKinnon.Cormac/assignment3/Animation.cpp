#include "Animation.h"


//constructor
Animation::Animation(GraphicsBuffer* pSpriteSheet, int spriteWidth, int spriteHeight, int numSpriteX, int numSpriteY, bool animate)
{
	mCurrentSprite = 0;
	mTotalSprites = 0;
	mTiming = 100.0;
	mPreviousFrameTime = 0;

	mAnimate = animate;
	//creates the individual sprites from the sprite sheet and adds them to the animation vector
	for (int x = 0; x < numSpriteX; x++) 
	{
		for (int y = 0; y < numSpriteY; y++) 
		{
			mpCurrentSprite = new Sprite((y * spriteWidth), (x * spriteHeight), spriteWidth, spriteHeight, pSpriteSheet);
			mTotalSprites ++;
			addSprites(mpCurrentSprite);
		}
	}

	mpAnimationTimer = new Timer();
	mpAnimationTimer->start();
}

//destructor
Animation::~Animation()
{
	for (int i = 0; i < mTotalSprites; i++)
	{
		delete mpListOfSprites[i];
	}

	mpListOfSprites.clear();

	delete mpAnimationTimer;
}
//adds a sprite to the vector of sprites
void Animation::addSprites(Sprite * sprite)
{
	mpListOfSprites.push_back(sprite);
}
//updates the animation when the frame is over
void Animation::update()
{
	if (mCurrentSprite < mpListOfSprites.size() - 1) 
	{
		mCurrentFrameTime = mpAnimationTimer->getElapsedTime();

		if (mCurrentFrameTime - mPreviousFrameTime > mTiming) 
		{
			mCurrentSprite += 1;
			mPreviousFrameTime = mCurrentFrameTime;
		}
	}
	else 
	{
		mCurrentSprite = 0;
	}
}
//accessor
Sprite* Animation::getCurrentSprite()
{
	return mpListOfSprites[mCurrentSprite];
}
//increases speed of the animation
void Animation::speedUpAnimation()
{
	mTiming -= 5.0;
}
//decreases speed of the animation
void Animation::speedDownAnimation()
{
	mTiming += 5.0;
}
