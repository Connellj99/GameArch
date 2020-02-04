#include "Animation.h"
#include "GraphicsBuffer.h"
#include "Timer.h"

using namespace std;

Animation::Animation(GBuffer *spriteSheet, double targetTime, bool loopAnim) //Add numRows x numCols of pictures in the spritesheet
{
	//chop up & use addSprite to store the sprites
	mTimeBetweenFrames = targetTime;
	mTimeUntilNextFrame = targetTime;
	mListIndex = 0;
	//mArrayCount = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{

			Sprite aSprite(spriteSheet, (spriteSheet->getWidth() / 4)*i, (spriteSheet->getHeight() / 4)*j, 60, 60);
			addSprite(aSprite);
			//mArrayCount++;
		}
	}
	mLoopCheck = loopAnim;
	setCurrentSprite(mSpriteVector.at(mListIndex));
}

Animation::Animation()
{

}

Animation::~Animation()
{
	/*for (int i = 0; i < 16; i++)
	{
		delete mSpriteList[i];
	}*/
}

void Animation::updateAnimation(double dTime)
{
	mTimeUntilNextFrame -= dTime;

	if (mTimeUntilNextFrame <= 0)
	{
		mListIndex++;
		if (mLoopCheck && mListIndex > 15)
		{
			mListIndex = 0;
		}

		setCurrentSprite(mSpriteVector.at(mListIndex));
		mTimeUntilNextFrame = mTimeBetweenFrames;
	}
}

void Animation::speedUp()
{
	mTimeBetweenFrames -= 25;
}

void Animation::slowDown()
{
	mTimeBetweenFrames += 25;
}

void Animation::addSprite(Sprite newSprite)
{
			mSpriteVector.push_back(newSprite);
}