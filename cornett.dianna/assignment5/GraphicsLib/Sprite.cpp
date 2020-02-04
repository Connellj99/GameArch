/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#include "Sprite.h"

/*
Height and width represent the size of the bitmap region that will be drawen
*/
Sprite::Sprite(GraphicsBuffer * graphicsBuffer, int sourceX, int sourceY, int width, int height)
{
	mpGraphicsBuffer = graphicsBuffer;
	mX = sourceX; //Where in bitmap to get region
	mY = sourceY;


	mWidth = width; //How big to make region
	mHeight = height;
};

