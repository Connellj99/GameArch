#include "Animation.h"
Animation::Animation() 
{
	mCurrentSprite = 0;
	mTotalSprites = 0;
	mCurrentSpeed = 100;
	mDefaultSpeed = 25;
	mAnimTimer.start();
	mLastTime = mAnimTimer.getElapsedTime();
}

void Animation::addTo(Sprite* newSprite) 
{
	mSpriteSheet.push_back(newSprite);
	mTotalSprites++;
}

void Animation::update()
{
	//Draw current sprite here
	if (mAnimTimer.getElapsedTime() > (mLastTime + mCurrentSpeed)) {
		mCurrentSprite++;
		if (mCurrentSprite == mTotalSprites) {
			mCurrentSprite = 0;
		}
		mLastTime = mAnimTimer.getElapsedTime();
	}
}

Sprite* Animation::getCurrentSprite() 
{
	return mSpriteSheet[mCurrentSprite];

}

Sprite* Animation::getSprite(int iter)
{
	return mSpriteSheet[iter];
}

void Animation::speedUp() 
{
	mCurrentSpeed += mDefaultSpeed;
}

void Animation::slowDown() 
{
	if (mCurrentSpeed - mDefaultSpeed != 0) 
	{
		mCurrentSpeed -= mDefaultSpeed;
	}
}

void Animation::loadFromBitmap(ALLEGRO_BITMAP* bmp, int width, int height, int x, int y) 
{
	GraphicsBuffer* newBuffer = new GraphicsBuffer(bmp);
	Sprite* newSprite = new Sprite(newBuffer, x, y, width, height);
	mSpriteSheet.push_back(newSprite);
	mTotalSprites++;
}

Animation::~Animation() {
	for (auto const& i : mSpriteSheet) 
	{
		delete i;
	}
}