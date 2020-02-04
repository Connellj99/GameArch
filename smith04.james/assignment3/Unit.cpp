#include "Unit.h"

Unit::Unit()
{
	mpAnim = new Animation();
}

Unit::~Unit()
{
	delete mpAnim;
}

void Unit::loadAnimation(GraphicsBuffer* spriteMap, int rows, int columns)
{
	mpAnim->loadSprites(spriteMap, rows, columns);
}

void Unit::update()
{
	mpAnim->update();
}

void Unit::draw()
{
	mpAnim->getCurrentSprite()->draw(x - (mpAnim->getCurrentSprite()->getWidth()/2.0), y - (mpAnim->getCurrentSprite()->getWidth() / 2.0));
}

void Unit::setAnim(Animation* newAnim)
{
	mpAnim = newAnim;
}

void Unit::setX(float xLoc)
{
	x = xLoc;
}

void Unit::setY(float yLoc)
{
	y = yLoc;
}

float Unit::getX()
{
	return x;
}

float Unit::getY()
{
	return y;
}