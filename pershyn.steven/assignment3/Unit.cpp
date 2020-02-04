/*
Author: Steven Pershyn
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is my own work, except where I referenced classmates' work and mentioned where relevant.
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

}

void Unit::update(double dt)
{
	mAnim->update(dt);
}

void Unit::draw()
{
	gpGame->mSystem->mGraphics.draw(mLoc.x, mLoc.y, mAnim->currentSprite());
}