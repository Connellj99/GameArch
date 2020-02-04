#include "Unit.h"
#include "Game.h"
#include "GraphicsSystem.h"


Unit::Unit()
{
	mAnimationsVec.clear();
}

Unit::Unit(Animation animation, Vector2D position)
{
	mAnimationsVec.push_back(animation);
	mPosition = position;
}

Unit::Unit(vector<Animation> animation, Vector2D position)
{
	mAnimationsVec = animation;
	mPosition = position;
}

Unit::Unit(Animation animation)
{
	mAnimationsVec.push_back(animation);
}

Unit::Unit(vector<Animation> animation)
{
	mAnimationsVec = animation;
}

Unit::~Unit()
{
}

void Unit::update()
{
	if (!mAnimationsVec.empty())
	{
		mAnimationsVec[mCurrentAnimation].update(mFrameTime);
	}
		
 	
}

void Unit::updateLocation(Vector2D newPosition)
{
	mPosition = newPosition;
 
}

void Unit::swapAnimations()
{
	mCurrentAnimation++;
	mCurrentAnimation = mCurrentAnimation % mAnimationsVec.size();
}

void Unit::draw()
{
	if (gpGameObject == nullptr || mAnimationsVec.empty())
	{
		return;
	}

	gpGameObject->getSystem()->getGraphicsSystem()->draw(mPosition, *mAnimationsVec[mCurrentAnimation].getCurrentSprite(), mScale);
}

Animation Unit::getCurrentAnimation()
{
	return mAnimationsVec[mCurrentAnimation];
}
