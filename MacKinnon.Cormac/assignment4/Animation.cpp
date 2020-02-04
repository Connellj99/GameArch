#include "Animation.h"


//constructor
Animation::Animation(GraphicsBuffer* pSpriteSheet, int spriteWidth, int spriteHeight, int numSpriteX, int numSpriteY, bool animate)
{
	mCurrentSprite = 0;
	mTotalSprites = 0;
	mTiming = 100.0;
	mPreviousFrameTime = 0;
	mTimeTillFrame = 100.0;

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
}

Animation::Animation(std::vector<Sprite*> spriteList)
{
	mpListOfSprites = spriteList;

	mCurrentSprite = 0;
	mTotalSprites = spriteList.size();
	mTiming = 100.0;
	mPreviousFrameTime = 0;
	mTimeTillFrame = 100.0;

	mAnimate = true;
}

//destructor
Animation::~Animation()
{
	//this is already done in the game's cleanup, but this should be given some kind of init thing so it doesn't need ot be commented out
	/*for (int i = 0; i < mTotalSprites; i++)
	{
		delete mpListOfSprites[i];
	}

	mpListOfSprites.clear();*/
}
//adds a sprite to the vector of sprites
void Animation::addSprites(Sprite * sprite)
{
	mpListOfSprites.push_back(sprite);
}
//updates the animation when the frame is over
void Animation::update(double time)
{
	mTiming -= time;
	if (mTiming <= 0.0) 
	{
		if (mAnimate) 
		{
			mCurrentSprite += 1;
			if (mCurrentSprite >= mpListOfSprites.size() - 1) 
			{
				mCurrentSprite = 0;
			}
			mTiming = mTimeTillFrame;
		}
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
	mTimeTillFrame -= 5.0;
}
//decreases speed of the animation
void Animation::speedDownAnimation()
{
	mTimeTillFrame += 5.0;
}

void Animation::animationState()
{
	mAnimate = !mAnimate;
}
