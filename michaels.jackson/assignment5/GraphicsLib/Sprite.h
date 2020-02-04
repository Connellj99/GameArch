/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include "Constants.h"
#include "GraphicsBuffer.h"
#include <PerformanceTracker.h>
#include <MemoryTracker.h>
class GraphicsBuffer;

class Sprite : public Trackable 
{
private:
	GraphicsBuffer* mBuffer;
	int mLocX, mLocY;
	int mWidth, mHeight;
public:
	Sprite(GraphicsBuffer*, int x = 0, int y = 0, int width = NULL, int height = NULL);

	GraphicsBuffer* getBuffer() { return mBuffer; };
	void setBuffer(GraphicsBuffer* buff) { mBuffer = buff; };

	int getLocX() { return mLocX; };
	int getLocY() { return mLocY; };
	void setLoc(int x, int y) { mLocX = x; mLocY = y; };


	int getWidth() { return mWidth; };
	int getHeight() { return mHeight; };
	void setDementions(int width, int height) { mWidth = width; mHeight = height; };
};