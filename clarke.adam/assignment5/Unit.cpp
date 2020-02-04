#include "Unit.h"
#include "Game.h"

Unit::Unit(std::map<std::string, Animation>& animations, const Vector2D& initLoc, const Vector2D& scale)
	: mAnimations(animations)
{
	mLocation = initLoc;
	mpCurAnimation = nullptr;
	mScale = scale;
}

Unit::~Unit()
{
}

Vector2D Unit::getDimensions() const
{
	// if no animation, no sprite is showing, so dimensions are (0, 0)
	if (!mpCurAnimation)
	{
		return Vector2D(0, 0);
	}
	const auto curSpriteDimensions = mpCurAnimation->getCurentSprite()->getDimensions();
	return Vector2D(curSpriteDimensions.getX() * mScale.getX(), curSpriteDimensions.getY() * mScale.getY());
}

void Unit::update(float curTime)
{
	// do not update if no animation or if pauseAnim
	if (mpCurAnimation && !pauseAnim)
	{
		mpCurAnimation->update(curTime);
	}
}

void Unit::draw() const
{
	if (!Game::getInstance() || !mpCurAnimation) return;

	Game::getInstance()->getSystem()->getGraphicsSystem()->draw(mLocation, *mpCurAnimation->getCurentSprite(), mScale);
}

bool Unit::intersects(const Vector2D& loc) const
{
	auto unitDim = getDimensions();
	return mLocation.getX() <= loc.getX()
		&& mLocation.getX() + unitDim.getX() >= loc.getX()
		&& mLocation.getY() <= loc.getY()
		&& mLocation.getY() + unitDim.getY() >= loc.getY();
}
