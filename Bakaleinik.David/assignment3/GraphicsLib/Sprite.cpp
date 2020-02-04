#include "Sprite.h"
#include "GraphicsBuffer.h"


Sprite::~Sprite()
{

}

Sprite::Sprite(GBuffer* name, int x, int y, int height, int width)
{
	mpSpriteBuffer = name;
	
	mSpriteHeight = height;
	mSpriteWidth = width;
	
	mSource_X = x;
	mSource_Y = y;
}

Sprite::Sprite()
{

}

int Sprite::getHeight()
{
	return mSpriteHeight;
}

int Sprite::getWidth()
{
	return mSpriteWidth;
}

int Sprite::getSourceLocX()
{
	return mSource_X;
}

int Sprite::getSourceLocY()
{
	return mSource_Y;
}

GBuffer* Sprite::getBuffer()
{
	return mpSpriteBuffer;
}