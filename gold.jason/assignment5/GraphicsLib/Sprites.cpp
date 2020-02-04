#include "Sprites.h"

Sprites::Sprites()
{
	mpSpriteBuffer = nullptr;
	mLocX = 0;
	mLocY = 0;
	mHeight = 0;
	mWidth = 0;
}

Sprites::Sprites(int height, int width, GraphicsBuffer* bufferpointer, int locX, int locY)
{
	mHeight = height;
	mWidth = width;
	mpSpriteBuffer = bufferpointer;
	mLocX = locX;
	mLocY = locY;
}

GraphicsBuffer* Sprites::getBuffer()
{
	return mpSpriteBuffer;
}

Sprites::~Sprites()
{

}