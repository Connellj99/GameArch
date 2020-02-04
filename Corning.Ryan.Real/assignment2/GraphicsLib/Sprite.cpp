#include "Sprite.h"

Sprite::Sprite(int locX, int locY, int mHeight, int mWidth, GraphicsBuffer * gBuffer)
{
	this->mlocX = locX;
	this->mlocY = locY;
	this->spriteHight = mHeight;
	this->spriteWidth = mWidth;
	this->gBuffer = gBuffer;
}

Sprite::~Sprite()
{

}
