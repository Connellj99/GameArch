#ifndef SPRITE_H
#define SPRITE_H

#include "Trackable.h"
#include "GraphicsBuffer.h"
#include "Vector2D.h"

class Sprite : public Trackable
{
public:
	//constuctors and acessors
	Sprite(GraphicsBuffer* graphicsBuffer, Vector2D sourceLoc,Vector2D dimensions);
	Sprite(GraphicsBuffer* graphicsBuffer);
	~Sprite();
	GraphicsBuffer* getGraphicsBuffer();
	Vector2D getLocation();
	Vector2D getDimensions();
	void updateLocation(Vector2D pos);

private:
	//Sprite top left corner locX,locY
	Vector2D mLoc;
	// Sprite Dimensions
	Vector2D mDimensions;
	// Pointer to GraphicsBuffer class
	GraphicsBuffer* mpGraficsBuffer;
};
#endif