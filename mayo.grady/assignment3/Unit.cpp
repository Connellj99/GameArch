/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Unit.h"

Unit::Unit(int xPos, int yPos)
{
	mLocation = Vector2D(xPos, yPos);
}

Unit::~Unit()
{
	
}

void Unit::update()
{
	mpAnimation->update();
}

void Unit::draw(int locX, int locY)
{
	gpGame->getSystem()->getGraphicsSystem()->draw(locX, locY, mpAnimation->getCurrentSprite()->getSpriteWidth(), mpAnimation->getCurrentSprite()->getSpriteHeight(), mpAnimation->getCurrentSprite(), BASE_SCALE);
}

void Unit::setAnimation(Animation * pAnimation)
{
	mpAnimation = pAnimation;
}