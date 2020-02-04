#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include "GraphicsBuffer.h"

using namespace std;


// This struct is meant to represent a 2D coordinate
struct Vector2 
{
	Vector2() 
	{
		mX = 0;
		mY = 0;
	}

	Vector2(int x, int y) 
	{
		mX = x;
		mY = y;
	}

	int mX;
	int mY;
};


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