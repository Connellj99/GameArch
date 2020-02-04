/*
Conner Root
EGP 310 - 01
*/

#include "Animation.h"

Animation::Animation()
{
}
Animation::Animation(GraphicsBuffer* gB, int w, int h, float s, bool l)
{
	int index = 0;
	int numCol = gB->getWidth() / w;
	int numRow = gB->getHeight() / h;

	Sprite* tempSprite;

	for (int i = 0; i < numRow; i++)
	{
		for (int j = 0; j < numCol; j++)
		{
			index = (i * 4) + j;

			tempSprite = new Sprite(gB, j*w, i*h, w, h);

			mpSpriteList.push_back(tempSprite);
		}
	}
	mpTimer = new Timer;
	mpTimer->start();
	mPrevTime = 0;

	tempSprite = nullptr;
	mSpriteIndex = 0;
	mSpeed = s;
	mLoop = l;
}

	// Update
void Animation::update()
{
	float currTime = mpTimer->getElapsedTime();

	if (mSpriteIndex < mpSpriteList.size())
	{
		if (currTime - mPrevTime > mSpeed)
		{
			mSpriteIndex++;
			if (mSpriteIndex >= mpSpriteList.size() && mLoop)
				mSpriteIndex = 0;
			mPrevTime = currTime;
		}
	}
}

// Speed function
void Animation::speedUp()
{
	if (mSpeed >= 0.0f)
		mSpeed -= SPEED_CHANGE;
	else
		mSpeed = 0.0f;
}

void Animation::slowDown() 
{
	mSpeed += SPEED_CHANGE;
}

// Destructor
Animation::~Animation()
{
	delete mpTimer;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			delete mpSpriteList[(4 * i) + j];
}