/*
Conner Root
EGP 310-01
*/

#include "Sprite.h"

// Constructors
Sprite::Sprite()
{
	mpBuffer = nullptr;
}
Sprite::Sprite(GraphicsBuffer* buffer, int xLoc, int yLoc, int spriteWidth, int spriteHeight)
{
	mpBuffer = buffer;
	mXPos = xLoc;
	mYPos = yLoc;
	mWidth = spriteWidth;
	mHeight = spriteHeight;
}

// Accessors
int Sprite::getXPos()
{
	return mXPos;
}

int Sprite::getYPos()
{
	return mYPos;
}

int Sprite::getWidth()
{
	return mWidth;
}

int Sprite::getHeight()
{
	return mHeight;
}

GraphicsBuffer* Sprite::getBuffer()
{
	return mpBuffer;
}

// Destructor
Sprite::~Sprite()
{
	//delete pBuffer;
}