#include "Centipede.h"
#include "Animation.h"
#include "Sprite.h"
#include "System.h"
#include "FileReader.h"


Centipede::Centipede(Sprite* image, int x, int y, int speed)
{
	mpBodySegment = image;
	mSourceX = x;
	mSourceY = y;
	mRunAnimation = false; //Temporary, will be updated when the other centipede features work
	mObjectType = "Centipede";
	mMoveSpeed = speed;
}

void Centipede::update(double dTime)
{
	if (!mShouldTurn)
	{
		mSourceX -= mMoveSpeed / 2;
	}
	else 
	{
		mSourceX += mMoveSpeed / 2;
	}
	
}

void Centipede::drawUnit(System* aSystem)
{
	aSystem->getDisplay()->draw(mSourceX, mSourceY, mpBodySegment, 1);
}