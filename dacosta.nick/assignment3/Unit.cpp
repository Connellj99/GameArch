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
#include "FontFlags.h"
#include "KeyCodes.h"

#include "Color.h"
#include "Font.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Animation.h"
#include "Unit.h"
#include "GraphicsSystem.h"
#include "System.h"
#include "Game.h"

// Constructor.
Unit::Unit()
{
	return;
}

// Destructor.
Unit::~Unit()
{
	return;
}

// Update the animation.
void Unit::update(double _deltaTime)
{
	mpAnimation->update(_deltaTime);
	return;
}

// Draw the current sprite at the current coordinates.
void Unit::draw(GraphicsSystem* _pGraphicsSystem)
{
	_pGraphicsSystem->draw(mpAnimation->getCurrentSprite(), mPositionX, mPositionY);
	return;
}

// Set the animation clip.
void Unit::setAnimation(Animation* _pAnimation)
{
	mpAnimation = _pAnimation;
	return;
}

// Set the position.
void Unit::setPosition(float _positionX, float _positionY)
{
	// Set the position of the unit to the middle of the sprite at the mouse position.
	mPositionX = _positionX - mpAnimation->getCurrentSprite().getWidth() / 2;
	mPositionY = _positionY - mpAnimation->getCurrentSprite().getHeight() / 2;
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