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

void Unit::update(double dT)
{
	mpAnimation->update(dT);
}

void Unit::setLocation(int x, int y)
{
	mLocation.setX(x);
	mLocation.setY(y);
}

void Unit::draw()
{
	Game::getInstance()->getSystem()->getGraphicsSystem()->draw(mLocation.getX(), mLocation.getY(), mpAnimation->getCurrentSprite()->getSpriteWidth(), mpAnimation->getCurrentSprite()->getSpriteHeight(), mpAnimation->getCurrentSprite(), BASE_SCALE);
}

void Unit::setAnimation(Animation * pAnimation)
{
	mpAnimation = pAnimation;
}