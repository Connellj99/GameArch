/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/


#include "Animation.h"
#include <iostream>
/*
Constructor initlizes varibles but does not add any sprites
*/
Animation::Animation(float timePerSprite, bool shouldLoop)
{
	mTimePerSprite = timePerSprite;
	mShouldLoop = shouldLoop;
}

/*
Destructor destorys all sprites
*/
Animation::~Animation() 
{
	for (Sprite * sprite : mSprites) 
	{
		delete sprite;
	}
}


/*
This function pushes a new sprite onto the end of mpSprites
*/
void Animation::addSprite(Sprite * sprite)
{
	mSprites.push_back(sprite);
}

/*
Time per frame is modified by amount.
*/
void Animation::changeAnimationSpeed(float amount)
{
	mTimePerSprite += amount;
}

/*
This function returns the current sprite
*/
Sprite * Animation::getCurrentSprite()
{
	return mSprites[mCurrentSpriteIndex];
}




/*
This function updates the current sprite index
*/
void Animation::update(double deltaTime) 
{
	mTimeCounter += deltaTime; //Add the delta time to the counter
	if (mTimeCounter > mTimePerSprite) //If the time counter is more then the time per frame then update the sprite index
	{

		mTimeCounter = 0;
		if (mCurrentSpriteIndex < mSprites.size() - 1) //Only update the counter if it is less then the length of the list (doing so must not cause it to overrun bounds)
		{
			mCurrentSpriteIndex++;
		}
		else 
		{ //If you are on the last sprite
			if (mShouldLoop) //If should loop was selected 
			{
				mCurrentSpriteIndex = 0; //Send the user back to the first sprite
			}
		}
	}
	
	
}

/*
This function reads a spritesheet with a given sheet and hight into the animation
*/
void Animation::readInSprites(GraphicsBuffer * spriteSheet, int spriteSheetWidth, int spriteSheetHeight)
{
	//Get the size of each sprite. Assuming dean sprites are same size as smurf sprites
	int spriteWidth = spriteSheet->getWidth() / spriteSheetWidth;
	int spriteHeight = spriteSheet->getWidth() / spriteSheetHeight;
	
	for (int i = 0; i < spriteSheetWidth; i++)
	{
		for (int j = 0; j < spriteSheetHeight; j++)
		{
			addSprite(new Sprite(spriteSheet, (j*spriteWidth), (i*spriteHeight), spriteWidth, spriteHeight));
		}
	}
}