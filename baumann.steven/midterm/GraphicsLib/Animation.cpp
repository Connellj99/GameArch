#include "Animation.h"
Animation::Animation() 
{
	mCurrentSprite = 0;
	mTotalSprites = 0;
}

void Animation::addTo(Sprite* newSprite) 
{
	mSpriteSheet.push_back(newSprite);
	mTotalSprites++;
}

void Animation::update()
{
	//Draw current sprite here

		mCurrentSprite++;
		if (mCurrentSprite == mTotalSprites) 
		{
			mCurrentSprite = 0;
		}

}

int Animation::getTotalSprites() 
{
	return mTotalSprites;
}

Sprite* Animation::getCurrentSprite() 
{
	return mSpriteSheet[mCurrentSprite];

}

Sprite* Animation::getSprite(int iter)
{
	return mSpriteSheet[iter];
}

GraphicsBuffer* Animation::loadFromBitmap(ALLEGRO_BITMAP* bmp, int width, int height, int x, int y) 
{
	GraphicsBuffer* newBuffer = new GraphicsBuffer(bmp);
	Sprite* newSprite = new Sprite(newBuffer, x, y, width, height);
	mSpriteSheet.push_back(newSprite);
	mTotalSprites++;
	return newBuffer;
}

Animation::~Animation() 
{
	for (auto const& i : mSpriteSheet) 
	{
		delete i;
	}
}