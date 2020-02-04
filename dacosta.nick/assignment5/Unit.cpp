/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <iostream>
#include <vector>

#include "Trackable.h"

#include "BufferFlags.h"
#include "FontFlags.h"

#include "Color.h"
#include "Font.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Animation.h"
#include "GraphicsSystem.h"
#include "Unit.h"

// Constructor.
Unit::Unit()
{
	return;
}

// Destructor.
Unit::~Unit()
{
	cleanUp();
	return;
}

// Clean up the unit.
void Unit::cleanUp()
{
	// Clean all the pointers in the animations list.
	for (size_t index = 0; index < mpAnimations.size(); index++)
	{
		if (mpAnimations[index] != nullptr)
		{
			// Clean the animation's pointer members.
			mpAnimations[index]->cleanUp();

			delete mpAnimations[index];
		}

		// Deallocate the memory.
		mpAnimations[index] = nullptr;
	}

	// Clear the list of all objects. (Extra precaution)
	mpAnimations.clear();

	// Deallocate the memory. (Again...)
	mpCurrentAnimation = nullptr;

	return;
}

// Update the animation if animate it on.
void Unit::update(double _deltaTime)
{
	if (mAnimate)
	{
		mpCurrentAnimation->update(_deltaTime);
	}

	return;
}

// Draw the current sprite at the current coordinates.
void Unit::draw(GraphicsSystem* _pGraphicsSystem)
{
	_pGraphicsSystem->draw(mpCurrentAnimation->getCurrentSprite(), mPositionX, mPositionY);
	return;
}

// Set the animation clip.
void Unit::setAnimation(Animation* _pAnimation)
{
	mpCurrentAnimation = _pAnimation;
	return;
}

// Add an animation clip.
void Unit::addAnimation(Animation* _pAnimation)
{
	mpAnimations.push_back(_pAnimation);

	return;
}

// Switch between animations.
void Unit::switchAnimation()
{
	if (mpCurrentAnimation == mpAnimations[0])
	{
		mpCurrentAnimation = mpAnimations[1];
	}
	else
	{
		mpCurrentAnimation = mpAnimations[0];
	}

	return;
}

// Set the position.
void Unit::setPosition(float _positionX, float _positionY)
{
	// Set the position of the unit to the middle of the sprite at the mouse position.
	mPositionX = _positionX - getWidth() / 2;
	mPositionY = _positionY - getHeight() / 2;
	return;
}

// Get the x coordinate.
float Unit::getPositionX()
{
	return mPositionX;
}

// Get the y coordinate.
float Unit::getPositionY()
{
	return mPositionY;
}

// Get the width.
int Unit::getWidth()
{
	return mpCurrentAnimation->getCurrentSprite().getWidth();
}

// Get the height.
int Unit::getHeight()
{
	return mpCurrentAnimation->getCurrentSprite().getHeight();
}

// Check for a collision at the given position.
bool Unit::collision(int _positionX, int _positionY)
{
	// Calculate the difference in position.
	int xPositionDifference = _positionX - mPositionX;
	int yPositionDifference = _positionY - mPositionY;

	// Return weather or not the collision is within the dimensions of the sprite.
	return xPositionDifference <= getWidth() && xPositionDifference >= 0 && yPositionDifference <= getHeight() && yPositionDifference >= 0;
}

// Toggle the animate setting on/off.
void Unit::toggleAnimate()
{
	mAnimate = !mAnimate;

	return;
}
