#include "Wall.h"
#include "Game.h"

Wall::Wall()
{
}

Wall::Wall(Vector2  newPos)
{
	mWallCurrentLocation = newPos;
}
Wall::~Wall()
{
	for (int i = 0, max = mCurrentAnimations.size(); i < max; i++)
	{
		mCurrentAnimations[i]->cleanupAnimation();
		delete mCurrentAnimations[i];
	}
}

void Wall::update(double newTimeBetweenFrames)
{
	// The following code updates the current frame of the animation
	mCurrentAnimations[mCurrentAnimationIndex]->update(newTimeBetweenFrames);

}

bool Wall::isVisible()
{
	// The following code checks if the current unit is within the current display window
	return mWallCurrentLocation.mX > 0 && mWallCurrentLocation.mX < DISP_WIDTH && mWallCurrentLocation.mY > 0 && mWallCurrentLocation.mY < DISP_HEIGHT;
}

void Wall::setAnimation(Animation & newAnimation)
{
	mCurrentAnimations.push_back(new Animation(newAnimation));
}

Animation * Wall::getCurrentAnimation()
{
	return mCurrentAnimations[mCurrentAnimationIndex];
}

void Wall::draw()
{
	Game::getStaticInstance()->getCurrentSystem()->getGraphicsSystem().draw(mWallCurrentLocation, *mCurrentAnimations[mCurrentAnimationIndex]->getCurrentSprite(), 0.5);
}

void Wall::swapAnimation()
{
	// The following code determines if the current animation is the
	// last animation in the animations vector. If it is, cycle back to 
	// the start of the vector other wise just go to the next animation.
	if (mCurrentAnimationIndex == mCurrentAnimations.size() - 1)
	{
		mCurrentAnimationIndex = 0;
	}
	else
	{
		mCurrentAnimationIndex++;
	}

}
