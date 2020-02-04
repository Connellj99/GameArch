#include "Game.h"
#include "Goomba.h"



// This function is the default constructor for this class
Goomba::Goomba() : Unit()
{
	mUnitType = GOOMBA;
	mVelocity = 0.0;
	mCurrentDirection = LEFT;
}





// This constructor creates the Goomba unit at a given unit
Goomba::Goomba(Vector2 newPos) 
{
	mUnitType = GOOMBA;
	mCurrentLocation = newPos;
	mVelocity = 0.0;
	mCurrentDirection = LEFT;
}





// This function is the destructor for this class
Goomba::~Goomba()
{
}





// This function is the default update for this class
void Goomba::update(double newTimeBetweenFrames)
{
	if (isAnimationStopped == false)
	{
		// The following code updates the current frame of the animation
		mCurrentAnimations[mCurrentAnimationIndex]->update(newTimeBetweenFrames);
	}

	// Check for collision here
	mVelocity += GRAVITY_SCALE;


	for (int i = 0; i < Game::getStaticInstance()->getUnitManager()->getSize(); i++)
	{
		if (Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mX > mCurrentLocation.mX - Game::getStaticInstance()->getPlayerBounds().mX &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mX < mCurrentLocation.mX + Game::getStaticInstance()->getPlayerBounds().mX &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY >(mCurrentLocation.mY + mVelocity) - Game::getStaticInstance()->getPlayerBounds().mY &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY < (mCurrentLocation.mY + mVelocity) + Game::getStaticInstance()->getPlayerBounds().mY
			)
		{
			if (Game::getStaticInstance()->getUnitManager()->getUnit(i) != this)
			{
				mVelocity = 0;
			}
		}
	}

	double minX = (mCurrentLocation.mX + GOOMBA_WALK_SPEED) - Game::getStaticInstance()->getPlayerBounds().mX;
	double maxX = (mCurrentLocation.mX + GOOMBA_WALK_SPEED) + Game::getStaticInstance()->getPlayerBounds().mX;
	double minY = mCurrentLocation.mY - Game::getStaticInstance()->getPlayerBounds().mY - 1;
	double maxY = mCurrentLocation.mY + Game::getStaticInstance()->getPlayerBounds().mY - 1;

	for (int i = 0; i < Game::getStaticInstance()->getUnitManager()->getSize(); i++)
	{
		if (Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mX > minX &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mX < maxX &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY > minY &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY < maxY
			)
		{
			if (Game::getStaticInstance()->getUnitManager()->getUnit(i) != this) 
			{
				if (mCurrentDirection == LEFT)
				{
					mCurrentDirection = RIGHT;
				}
				else
				{
					mCurrentDirection = LEFT;
				}
			}
		}
	}


	switch (mCurrentDirection)
	{
	case LEFT:
		moveToPosition(Vector2(mCurrentLocation.mX - GOOMBA_WALK_SPEED, mCurrentLocation.mY + mVelocity));
		break;
	case RIGHT:
		moveToPosition(Vector2(mCurrentLocation.mX + GOOMBA_WALK_SPEED, mCurrentLocation.mY + mVelocity));
		break;
	case NONE:
		break;
	default:
		break;
	}
}