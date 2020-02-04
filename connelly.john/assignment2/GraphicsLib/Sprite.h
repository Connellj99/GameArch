#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include "GraphicsBuffer.h"

using namespace std;

struct Vector2 {
	Vector2() 
	{
		sX = 0;
		sY = 0;
	}

	Vector2(int x, int y) 
	{
		sX = x;
		sY = y;
	}

	int sX;
	int sY;
};


class Sprite : public Trackable
{
public:
	Sprite();
	~Sprite();
	int getLength();
	int getWidth();
	GraphicsBuffer getGraphicsBuffer();
	Vector2 getLoc();


private:
	GraphicsBuffer mGraphicsBuffer;
	Vector2 mLocation;
	int mLength;
	int mWidth;
};

#endif 