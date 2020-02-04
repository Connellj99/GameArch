#include "Mushroom.h"
#include "System.h"

Mushroom::Mushroom(std::vector<Sprite> sprites, int x, int y)
{
	mMushroomHP = 4;
	mSourceX = x;
	mSourceY = y;

	mSpriteVector = sprites;
	mCurrentSprite = mSpriteVector.at(0);
	mObjectType = "Mushroom";

	mRunAnimation = false;
}

void Mushroom::showDamage()
{
	if (mMushroomHP == 3)
	{
		mCurrentSprite = mSpriteVector.at(1);
	}
	else if (mMushroomHP == 2)
	{
		mCurrentSprite = mSpriteVector.at(2);
	}
	else if (mMushroomHP == 1)
	{
		mCurrentSprite = mSpriteVector.at(3);
	}
}

void Mushroom::drawUnit(System* aSystem)
{
	//aSystem->getDisplay()->draw(mSourceX, mSourceY, &mSpriteVector.at(0), (double)1 / 2, mSpriteVector.at(0).getHeight(), mSpriteVector.at(0).getWidth(), 0, 0);
	aSystem->getDisplay()->draw(mSourceX, mSourceY, &mCurrentSprite, (double)1/6 );

}