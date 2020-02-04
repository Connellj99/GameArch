#include "Sprite.h"

Sprite::Sprite()
{
	mpGraphicsBuffer = nullptr;
}

Sprite::Sprite(float x, float y, float w, float h, GraphicsBuffer* buff)
{
	xloc = x;
	yloc = y;
	width = w;
	height = h;
	mpGraphicsBuffer = buff;
}

Sprite::~Sprite()
{
	//delete mpGraphicsBuffer; Doesn't work when several sprites call the same GraphicsBuffer. Keeping as a reminder.
}

float Sprite::getHeight()
{
	return height;
}

float Sprite::getWidth()
{
	return width;
}

float Sprite::getX()
{
	return xloc;
}

float Sprite::getY()
{
	return yloc;
}

GraphicsBuffer* Sprite::getBuffer()
{
	return mpGraphicsBuffer;
}

void Sprite::draw(float x, float y)
{
	al_draw_bitmap_region(mpGraphicsBuffer->getBitMap(), xloc, yloc, width, height, x, y, 0);
}