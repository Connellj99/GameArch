/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#pragma once
#include "GraphicsBuffer.h"

/*
This class is a Font that can be drawen to the screen using graphics system
*/
class Sprite : public Trackable
{

private:
	GraphicsBuffer * mpGraphicsBuffer;
	int mX;
	int mY;
	int mWidth;
	int mHeight;


public:
	Sprite(GraphicsBuffer * graphicsBuffer, int sourceX, int sourceY, int width, int height);

	~Sprite() 
	{
	};

	//Getters
	int getSourceX()
	{ 
		return mX; 
	}

	int getSourceY() 
	{ 
		return mY; 
	}

	int getWidth() 
	{ 
		return mWidth; 
	}

	int getHeight() 
	{
		return mHeight;
	}

	GraphicsBuffer * getGraphicsBuffer()
	{
		return mpGraphicsBuffer; 
	}
	
};