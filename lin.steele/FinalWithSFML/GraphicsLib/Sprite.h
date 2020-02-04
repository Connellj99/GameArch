#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include "GraphicsBuffer.h"
#include "Vector2.h"

using namespace std;


class Sprite : public Trackable
{
public:


	// Constructors
	Sprite();
	Sprite( string spriteFilePath, int locationX, int locationY );
	Sprite( GraphicsBuffer * newBuffer, int locationX, int locationY, bool isPartOfAnimation, Vector2 dimensions );

	// Destructors
	~Sprite();

	// Acessors
	int getHeight();
	int getWidth();
	GraphicsBuffer * getGraphicsBuffer();
	Vector2 getLoc();

	void changeLoc(int newX, int newY);

	Vector2 getDisplacement();

private:

	// Buffers
	GraphicsBuffer * mGraphicsBuffer;

	// Vector2's
	Vector2 mLocation;

	// Floats
	int mHeight;
	int mWidth;

	int mDisplacementX;
	int mDisplacementY;

	bool mIsPartOfAnAnimation;

	Vector2 mDimensions;
};

#endif // SPRITE_H