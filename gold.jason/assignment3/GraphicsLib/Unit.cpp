#include "Unit.h"

Unit::Unit()
{
	return;
}

void Unit::draw()
{

}

void Unit::update()
{

}

Animation Unit::setAnimation()
{
	return Animation();
}

Unit::~Unit()
{
	smurfAnim->~Animation();
	deanAnim->~Animation();
}
