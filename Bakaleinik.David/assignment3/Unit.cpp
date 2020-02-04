#include "Unit.h"
#include "System.h"

using namespace std;

Unit::Unit(Animation* defaultAnim, int x, int y)
{
	mSourceX = x;
	mSourceY = y;

	mUnitAnimation = defaultAnim;
}

Unit::Unit()
{

}

Unit::~Unit()
{

}

void Unit::update(double dTime)
{
	mUnitAnimation->updateAnimation(dTime);
}

void Unit::drawUnit(System* aSystem)
{
	aSystem->getDisplay()->draw(mSourceX, mSourceY, &(mUnitAnimation->getCurrentSprite()), 1, 60, 60, mUnitAnimation->getCurrentSprite().getSourceLocX(), mUnitAnimation->getCurrentSprite().getSourceLocY());
}

void Unit::setUnitAnimation(Animation* target)
{
	mUnitAnimation = target;
}