/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#include "Unit.h"
#include "Game.h"

Unit::Unit(int x, int y)
{
	mLoc.x = x;
	mLoc.y = y;
}


Unit::~Unit()
{
	if (mAnim != nullptr)
	{
		delete mAnim;
	}
}

void Unit::update(double dt)
{
	if (mAnimate && mAnim)
		mAnim->update(dt);
}

void Unit::draw(float scale)
{
	if (mAnim)
	{
		Game::getInstance()->getSystem()->mGraphics.draw(mAnim->currentSprite(), mLoc.x, mLoc.y, scale);
	}
}