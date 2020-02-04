#include "Sprite.h"

Sprite::Sprite(GraphicsBuffer* graphicsBuffer)
	:mpGraphicsBuffer(graphicsBuffer)
{
}


Sprite::Sprite(GraphicsBuffer* graphicsBuffer, const Vector2D& sourceLoc, const Vector2D& dimensions)
	: mpGraphicsBuffer(graphicsBuffer), mSourceLocation(sourceLoc), mDimensions(dimensions)
{
}

Sprite::~Sprite()
{
}