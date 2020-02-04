#include "Sprite.h"

Sprite::Sprite(GraphicsBuffer* graphicsBuffer, const Vector2D& sourceLoc, const Vector2D& dimensions)
	: mpGraphicsBuffer(graphicsBuffer), mSourceLocation(sourceLoc), mDimensions(dimensions)
{
}

Sprite::Sprite(const Sprite& rhs)
	: mpGraphicsBuffer(rhs.mpGraphicsBuffer), mSourceLocation(rhs.mSourceLocation),
	  mDimensions(rhs.mDimensions)
{

}

Sprite::~Sprite()
{
}
