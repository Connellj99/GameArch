/*
Conner Root
EGP 310 - 01
*/

#include "Animation.h"

Animation::Animation()
{
}
Animation::Animation(GraphicsBuffer* gB, int wdth, int hght, float sp, bool loop)
{
	int index = 0;
	int numCol = gB->getWidth() / wdth;
	int numRow = gB->getHeight() / hght;

	Sprite* tempSprite;

	for (int i = 0; i < numRow; i++)
	{
		for (int j = 0; j < numCol; j++)
		{
			index = (i * numRow) + j;

			tempSprite = new Sprite(gB, j*wdth, i*hght, wdth, hght);

			mpSpriteList.push_back(tempSprite);
		}
	}

	mpTimer = new Timer;
	mpTimer->start();
	mPrevTime = 0;

	tempSprite = nullptr;
	mSpriteIndex = 0;
	mSpeed = sp;
	mLoop = loop;
}

	// Update
void Animation::update()
{
	if (mLoop)
	{
		float currTime = mpTimer->getElapsedTime();

		if (mSpriteIndex < (int)mpSpriteList.size() && !mPaused)
		{
			if (currTime - mPrevTime > SPEED_BASE / mSpeed)
			{
				mSpriteIndex++;
				if (mSpriteIndex >= (int)mpSpriteList.size())
					mSpriteIndex = 0;
				mPrevTime = currTime;
			}
		}
	}
}

// Speed function
void Animation::speedUp()
{
	mSpeed += SPEED_CHANGE;
}

void Animation::slowDown() 
{
	mSpeed -= SPEED_CHANGE;
	if (mSpeed <= 0.0f)
		mSpeed = 0.05f;
}

// Destructor
Animation::~Animation()
{
	delete mpTimer;
	for (int i = 0; i < (int)mpSpriteList.size(); i++)
		delete mpSpriteList[i];
}