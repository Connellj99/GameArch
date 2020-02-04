/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 3											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <iostream>

#include "Trackable.h"

#include "BufferFlags.h"

#include "Color.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Animation.h"

// Number of milliseconds in a second.
const double SECONDS_TO_MILLISECONDS = 1000;

// Default animation speed at 12 frames per second.
const double DEFAULT_ANIMATION_SPEED = 12;

// Constructor.
Animation::Animation()
{
	return;
}

// Destructor.
Animation::~Animation()
{
	mpAnimationClip = nullptr;
	return;
}

// Initialize the animation with a clip, size and speed.
void Animation::initialize(Sprite* _pSprites, int _size)
{
	// Assign the spites to the sprite animation clip.
	mpAnimationClip = _pSprites;

	// Set the number of sprites in the animation clip.
	mClipSize = _size;

	// Set the default animation speed.
	mSpeed = DEFAULT_ANIMATION_SPEED;

	return;
}

// Update the animation.
void Animation::update(double _deltaTime)
{
	// Add the time difference to the animation time difference tracker.
	mDeltaTime += _deltaTime;

	// Check if it is time to go to the next sprite.
	if (mDeltaTime >= SECONDS_TO_MILLISECONDS / mSpeed)
	{
		// Get the remainder if the time difference is over the animation frame rate.
		mDeltaTime = std::fmod(mDeltaTime, mSpeed);

		// Proceed to the next sprite in the clip and back to the beginning if it's at the end.
		mCurrentIndex = (mCurrentIndex + 1) % mClipSize;
	}
	return;
}

// Set the animation clip.
void Animation::setAnimationClip(Sprite* _pSprites, int _size)
{
	// Assign the spites to the sprite animation clip.
	mpAnimationClip = _pSprites;

	// Set the number of sprites in the animation clip.
	mClipSize = _size;
	return;
}

// Get the current sprite in the animation.
Sprite Animation::getCurrentSprite()
{
	return mpAnimationClip[mCurrentIndex];
}

// Get the current animation clip.
Sprite* Animation::getCurrentClip()
{
	return mpAnimationClip;
}

// Speed adjuster.
void Animation::adjustSpeed(double _speedMultiplier)
{
	// Change the speed based on the given multipler.
	mSpeed *= _speedMultiplier;
	return;
}