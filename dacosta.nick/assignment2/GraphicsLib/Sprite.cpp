/*********************************************************************
**		Author:														**
**		Class: 310 <Section 0>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
**		Assingment 2 Author: Nick DaCosta							**
*********************************************************************/
#include "Sprite.h"

// Default constructor.
Sprite::Sprite()
{
	return;
}

// Copy constructor.
Sprite::Sprite(Sprite& _oldSprite)
{
	mSourceX = _oldSprite.mSourceX;
	mSourceY = _oldSprite.mSourceY;
	mWidth = _oldSprite.mWidth;
	mHeight = _oldSprite.mHeight;
	mpBuffer = _oldSprite.mpBuffer;

	return;
}

// Create a sprite with the given specifications.
Sprite::Sprite(GraphicsBuffer* _pBuffer, int _sourceX, int _sourceY, int _width, int _height)
{
	// Assign the member variables their designated values.
	mpBuffer = _pBuffer;
	mSourceX = _sourceX;
	mSourceY = _sourceY;
	mWidth = _width;
	mHeight = _height;
	return;
}

// Clean up the sprite instance.
Sprite::~Sprite()
{
	return;
}

// Get the source x location on the buffer.
int Sprite::getSourceX()
{
	return mSourceX;
}

// Get the source y location on the buffer.
int Sprite::getSourceY()
{
	return mSourceY;
}

// Get the width.
int Sprite::getWidth()
{
	return mWidth;
}

// Get the height.
int Sprite::getHeight()
{
	return mHeight;
}

// Get the buffer associated with this sprite.
GraphicsBuffer* Sprite::getBuffer()
{
	return mpBuffer;
}