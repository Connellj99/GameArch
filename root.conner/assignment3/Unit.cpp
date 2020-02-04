/*
Conner Root
EGP 310 - 01
*/

#include "Unit.h"
#include "Game.h"

// Constructor
Unit::Unit()
{
	mXPos = 0;
	mXPos = 0;
}
Unit::Unit(int x, int y, Animation* a)
{
	mXPos = x;
	mXPos = y;
	mpAnim = a;
}

// Update
void Unit::setLocation(int x, int y)
{
	mXPos = x - 30;
	mYPos = y - 30;
}

void Unit::update()
{
	mpAnim->update();
}

// Draw
void Unit::draw()
{
	pGameObj->getSystem()->getGraphicsSystem()->draw(mXPos, mYPos, mpAnim->getCurrentSprite(), 1.0);
}

// Switch to a new animation
void Unit::setAnimation(Animation* a)
{
	mpAnim = a;
}

// Destructor
Unit::~Unit()
{
	mpAnim = nullptr;
}