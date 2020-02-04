#include "Animations.h"
#include "Sprites.h"

Animations::Animations(float time, bool canLoop)
{
	mTimer = time;
	mCanLoop = canLoop;
}

Animations::~Animations()
{
	// Delete all sprites in the animation clip
	for (int i = 0; i < mpListOfAnimations.size(); i++)
	{
		delete mpListOfAnimations[i];
	}
	mpListOfAnimations.clear();
}

void Animations::updateAnimation(float timeAmt)
{

	mTimeCount += timeAmt;


	if (mTimeCount > mTimePerFrame && mCurrentSpriteIndex < mpListOfAnimations.size())
	{
		mCurrentSpriteIndex++;//add a counter to the index
		mTimeCount = 0;

		if (mCurrentSpriteIndex >= mpListOfAnimations.size() && mCanLoop)//if the current index is greater than the size of the vector, reset
		{
			mCurrentSpriteIndex = 0;
		}
	}
	
}

Sprite* Animations::getCurrentSprite()
{
	return mpListOfAnimations[mCurrentSpriteIndex];//return the list of animations at said index
}

void Animations::cleanUpSpriteAnims()
{

}

void Animations::addSprite(Sprite * spriteToBeAdded)
{
	mpListOfAnimations.push_back(spriteToBeAdded);	//push to the list of animations, the passed in sprite
}

void Animations::chopSpriteSheet(GraphicsBuffer& passedBuffer)
{
	Sprite* tmp;
	bool once = false;
	
	//creates a new sprite with the passed in buffer and the width and all divided by 4.
	tmp = new Sprite(&passedBuffer,0.0f,0.0f,passedBuffer.mBuffWidth/DIMENSIONS,passedBuffer.mBuffHeight/DIMENSIONS);

	//does it again with another width variable
	tmp->setSpriteWidth(passedBuffer);
	//does it again with another height variable
	tmp->setSpriteHeight(passedBuffer);

	for (mAnimationsY; mAnimationsY < DIMENSIONS; mAnimationsY++)
	{
	//	tmp->setSpriteHeight
	
		tmp->graphicBuffObject.mBuffWidth = tmp->graphicBuffObject.mBuffWidth + (tmp->getSpriteWidth()* mAnimationsX);
		tmp->graphicBuffObject.mBuffHeight = tmp->graphicBuffObject.mBuffHeight + (tmp->getSpriteHeight()  * mAnimationsY);
	
		if (once == false)//this will just set the first 0,0 positon of first sprite thats all
		{
			addSprite(tmp);
			once = true;
		}
		else//every other sprite is done here
		{
			addSprite(tmp = new Sprite(&passedBuffer, tmp->graphicBuffObject.mBuffWidth, tmp->graphicBuffObject.mBuffHeight, tmp->getSpriteWidth(), tmp->getSpriteHeight()));
		}
		
		//add to the number of smurfs that have been drawn
		mTotalAnimations++;

		//add one to the x so that way itll go to the one to the right
		mAnimationsX++;
		
		for (mAnimationsX; mAnimationsX < DIMENSIONS; mAnimationsX++)
		{
			//set the sprites buffer width to the this mathematical equation that takes takes the current width and or hieght and adds 60 * the current index x or y.
			tmp->graphicBuffObject.mBuffWidth = tmp->graphicBuffObject.mBuffWidth + (tmp->getSpriteWidth() * mAnimationsX);
			tmp->graphicBuffObject.mBuffHeight = tmp->graphicBuffObject.mBuffHeight + (tmp->getSpriteHeight() * mAnimationsY);
		
			addSprite(tmp = new Sprite(&passedBuffer, tmp->graphicBuffObject.mBuffWidth, tmp->graphicBuffObject.mBuffHeight, tmp->getSpriteWidth(), tmp->getSpriteHeight()));//then pass that information as a new sprite.

			tmp->addNumOfSmurfs();//add the number of smurfs
			mTotalAnimations++;//add to the number of animations added

		}
		mAnimationsX = 0;//reset before going to top, that way we can get 0 position x and the next y
	};
}

void Animations::changeAnimationSpeed(bool speedUp,bool speedDown)
{

	switch (speedUp)
	{
	case (true):	//if we speed up
		adjustAnimationSpeed(-TIME_PER_FRAME_MODIFIER);
	
		break;

	case(false)://else do nothing

		break;

	}
	
	switch (speedDown)
	{
	case (true)://if we speed down
		adjustAnimationSpeed(TIME_PER_FRAME_MODIFIER);
		break;

	case(false)://else do nothing

		break;

	}
}

void Animations::adjustAnimationSpeed(float adjustmentAmt)
{
	mTimePerFrame = mTimePerFrame + adjustmentAmt;//change the time per frame to the old + whatever adjustment Amt is
}
