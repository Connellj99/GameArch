/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Sprite.h"

Sprite::Sprite( int LocX, int LocY, int width, int height, GraphicsBuffer* pBuffer )
{
	this->mLocX = LocX;
	this->mLocY = LocY;
	this->mSpriteHeight = height;
	this->mSpriteWidth = width;
	this->mpGraphicsBuffer = pBuffer;
}

Sprite::~Sprite()
{
	
}
