#include "Unit.h"
#include "Game.h"

Unit::Unit(Animation* animation, const Vector2D& initLoc, const Vector2D& scale)
{
	mLocation = initLoc;
	mpAnimation = animation;
	mScale = scale;
}

Unit::Unit(const Vector2D& initLoc, const Vector2D& scale)
{
	mLocation = initLoc;
	mpAnimation = nullptr;
	mScale = scale;
}

Unit::~Unit()
{
}

void Unit::setAnimation(Animation* animation)
{
	mpAnimation = animation;
}

void Unit::update()
{
	mpAnimation->update();
}

void Unit::draw() const
{
	if (gpGame == nullptr || mpAnimation == nullptr) return;

	gpGame->getSystem()->getGraphicsSystem()->draw(mLocation, *mpAnimation->getCurentSprite(), mScale);
}
