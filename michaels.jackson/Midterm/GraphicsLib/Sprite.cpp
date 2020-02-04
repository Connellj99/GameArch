/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Sprite.h"
#include "GraphicsBuffer.h"
/*#################################
			Sprite
#################################*/
Sprite::Sprite(GraphicsBuffer* buffer, int x, int y, int width, int height, bool owns) 
{
	mOwnBuffer = owns;
	mBuffer = buffer;
	mLocX = x;
	mLocY = y;
	if (width == NULL) 
	{
		mWidth = mBuffer->getWidth();
		mHeight = mBuffer->getHeight();
	}
	else 
	{
		mWidth = width;
		mHeight = height;
	}
}
