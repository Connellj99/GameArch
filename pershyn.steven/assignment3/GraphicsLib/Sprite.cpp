/*
Author: Steven Pershyn
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is my own work, except where I referenced classmates' work and mentioned where relevant.
*/
#include "Sprite.h"


Sprite::Sprite()
{
	mX = 0;
	mY = 0;
	mWidth = 0;
	mHeight = 0;
	mpGraphicsBuffer = NULL;
}

Sprite::Sprite(int locX, int locY, int width, int height, GraphicsBuffer* graphicsBuffer)
{
	mX = locX;
	mY = locY;
	mWidth = width;
	mHeight = height;
	mpGraphicsBuffer = graphicsBuffer;

}

Sprite::~Sprite()
{
	
}

int Sprite::getWidth()
{
	return mWidth;
}

int Sprite::getHeight()
{
	return mHeight;
}

int Sprite::getX()
{
	return mX;
}

int Sprite::getY()
{
	return mY;
}

GraphicsBuffer* Sprite::getGraphicsBuffer()
{
	return mpGraphicsBuffer;
}