/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Midterm
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "PowerUp.h"

PowerUpObj::PowerUpObj(Point loc, PowerUp power, GraphicsBuffer* buff, float targetSize)
{
	mTargetSize = targetSize;
	mLoc = loc;
	mPower = power;
	Animation* anim = new Animation(16);
	anim->addSpriteSheet(buff,2,3);
	setAnimation(anim);
}

void PowerUpObj::draw(float scale)
{
	scale = mTargetSize / mAnim->currentSprite()->getWidth();
	Unit::draw(scale);
}
