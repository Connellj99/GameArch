#include "Sprite.h"

//default constructor
Sprite::Sprite() 
{
	mSourceLocX = 0;
	mSourceLocY = 0;
	mWidth = 0;
	mHeight = 0;
	mpGraphicsBuffer = NULL;
}

//constructor
Sprite::Sprite(int sourceLocX, int sourceLocY, int width, int height, GraphicsBuffer* pGraphicsBuffer)
{
	mSourceLocX = sourceLocX;
	mSourceLocY = sourceLocY;
	mWidth = width;
	mHeight = height;
	mpGraphicsBuffer = pGraphicsBuffer;

}


Sprite::~Sprite()
{
}

//accessors
GraphicsBuffer* Sprite::getGraphicsBuffer() 
{
	return mpGraphicsBuffer;
}

int Sprite::getHeight() 
{
	return mHeight;
}

int Sprite::getWidth() 
{
	return mWidth;
}

float Sprite::getSourceLocX()
{
	return mSourceLocX;
}

float Sprite::getSourceLocY()
{
	return mSourceLocY;
}
