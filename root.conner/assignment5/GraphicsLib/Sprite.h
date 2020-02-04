/*
Conner Root
EGP 310-01
*/

#pragma once

#include "GraphicsLib.h"
#include "GraphicsBuffer.h"

class Sprite : public Trackable
{
private:
	GraphicsBuffer* mpBuffer;
	int mXPos, mYPos;
	int mWidth, mHeight;

public:
	// Constructors
	Sprite();
	Sprite(GraphicsBuffer*, int, int, int, int);

	// Accessors
	int getXPos();
	int getYPos();
	int getWidth();
	int getHeight();
	GraphicsBuffer* getBuffer();

	// Destructor
	~Sprite();
};