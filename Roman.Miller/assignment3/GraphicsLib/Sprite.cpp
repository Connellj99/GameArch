#include "Sprite.h"
//constuctor
Sprite::Sprite(GraphicsBuffer * graphicsBuffer, Vector2D sourceLoc, Vector2D dimensions)
{
	mLoc = sourceLoc;
	mDimensions = dimensions;
	mpGraficsBuffer = graphicsBuffer;
}

Sprite::Sprite(GraphicsBuffer * graphicsBuffer)
{
	mpGraficsBuffer = graphicsBuffer;
}

Sprite::~Sprite()
{
	//delete mpGraficsBuffer;
}
//acessors
GraphicsBuffer* Sprite::getGraphicsBuffer()
{
	return mpGraficsBuffer;
}

Vector2D Sprite::getLocation()
{
	return mLoc;
}

Vector2D Sprite::getDimensions()
{
	return mDimensions;
}

void Sprite::updateLocation(Vector2D pos)
{
	mLoc = pos;
}
