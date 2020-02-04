#include "Unit.h"
#include "Game.h"

Unit::Unit(CollisionSystem* collisionMap, const std::string& tag)
	: BoxCollider2D(tag, Vector2D(0, 0), Vector2D(0, 0), collisionMap)
{
}

Unit::Unit(std::map<std::string, Animation>& animations, const Vector2D& scale,
	const Vector2D& initLoc, CollisionSystem* collisionMap, const std::string& tag)
	: BoxCollider2D(tag, Vector2D(0, 0), mDimensions, collisionMap), mAnimations(animations),
	mLocation(initLoc)
{
	mpCurAnimation = nullptr;
	mScale = scale;
}

Unit::~Unit()
{
}

void Unit::calcDimensions()
{
	const auto curSpriteDimensions = mpCurAnimation->getCurentSprite()->getDimensions();
	mDimensions = Vector2D(curSpriteDimensions.getX() * mScale.getX(),
		curSpriteDimensions.getY() * mScale.getY());
	BoxCollider2D::setDim(mDimensions);
}

void Unit::update(float curTime)
{
	if (!mIsActive) return;

	// do not update if no animation or if pauseAnim
	if (mpCurAnimation && !mPauseAnim)
	{
		mpCurAnimation->update(curTime);
	}
}

void Unit::draw() const
{
	if (!Game::getInstance() || !mpCurAnimation || !mIsActive) return;

	Game::getInstance()->getSystem()->getGraphicsSystem()->draw(mLocation,
		*mpCurAnimation->getCurentSprite(), mScale, mFlipHorizontal);
}

void Unit::setAnimation(const AnimKey& key)
{
	mpCurAnimation = &mAnimations[key];
	mpCurAnimation->reset();
	calcDimensions();
}

void Unit::addAnimation(const AnimKey& key, Animation animation)
{
	mAnimations.insert({ key, animation });
}

bool Unit::intersects(const Vector2D& loc) const
{
	auto unitDim = getDimensions();
	return mLocation.getX() <= loc.getX()
		&& mLocation.getX() + unitDim.getX() >= loc.getX()
		&& mLocation.getY() <= loc.getY()
		&& mLocation.getY() + unitDim.getY() >= loc.getY();
}
