#pragma once

#include "GraphicsLib.h"
#include "GraphicsBuffer.h"

class Sprite : public Trackable{
private:

	GraphicsBuffer* mBuff;
	int mWidth;
	int mHeight;
	int LOC_X;
	int LOC_Y;

public:

	//getters
	int getLocX();
	int getLocY();
	int getWidth();
	int getHeight();
	GraphicsBuffer* getBuffer();

	//constructors
	Sprite();
	Sprite(GraphicsBuffer*, int, int, int, int);

	//destructor
	~Sprite();
};