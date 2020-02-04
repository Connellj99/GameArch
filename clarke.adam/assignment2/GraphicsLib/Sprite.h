#ifndef SPRITE_H
#define SPRITE_H

#include "Trackable.h"
#include "GraphicsBuffer.h"
#include "Vector2D.h"

// A pointer to a specific part of a GraphicsBuffer
class Sprite : public Trackable
{
public:
	Sprite(GraphicsBuffer* graphicsBuffer);
	Sprite(GraphicsBuffer* graphicsBuffer, const Vector2D& sourceLoc, const Vector2D& dimensions);
	//Sprite(GraphicsBuffer* graphicsBuffer, const std::string& filename, const Vector2D& sourceLoc, const Vector2D& dimensions);
	~Sprite();

	GraphicsBuffer* getGraphicsBuffer() const { return mpGraphicsBuffer; }
	Vector2D getSourceLocation() const { return mSourceLocation; }
	Vector2D getDimensions() const { return mDimensions; }
private:
	// the graphics buffer this sprite points to
	GraphicsBuffer* mpGraphicsBuffer;
	// upper left-hand corner of where sprite begins
	Vector2D mSourceLocation;
	// width and height of sprite
	Vector2D mDimensions;
};
#endif