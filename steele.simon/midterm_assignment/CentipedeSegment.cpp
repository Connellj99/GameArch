#include "CentipedeSegment.h"
#include "UnitManager.h"
#include "Game.h"



// This function is the default constructor of the class
CentipedeSegment::CentipedeSegment() : Unit()
{
	mUnitType = NONE;
	mCurrentDirection = RIGHT;
	mLastHorizontalDirection = LEFT;
	mVerticalDirection = DOWN;
	mRemainingTime = 0;
	mTimeElapsed = Game::getStaticInstance()->getCentipedeSpeed();
}





// This constructor initializes all variables and moves
// the Centipede segment to a specific position
CentipedeSegment::CentipedeSegment(Vector2 newPos)
{
	mCurrentLocation = newPos;
	isAnimationStopped = false;
	mUnitType = CENTIPEDE_SEGMENT;
	mCurrentDirection = RIGHT;
	mLastHorizontalDirection = LEFT;
	mVerticalDirection = DOWN;
	mRemainingTime = 0;
	mTimeElapsed = Game::getStaticInstance()->getCentipedeSpeed();
	mHasBeenMovedByMushroom = false;
}





// This is the default destructor of the class
CentipedeSegment::~CentipedeSegment()
{
}





// This function adds a pointer to the next segment before the current segment
void CentipedeSegment::addNextSegment(CentipedeSegment * newSegment) 
{
	mNext = newSegment;
}





// This function adds a pointer to the next segment after the current segment
void CentipedeSegment::addLastSegment(CentipedeSegment * newSegment) 
{
	mLast = newSegment;
}





// This function is the update function for this class
void CentipedeSegment::update(double newTimeBetweenFrames)
{
	mTimeElapsed -= newTimeBetweenFrames;

	if (mTimeElapsed <= 0.0 && mNext == nullptr) 
	{
		if (mLast != nullptr)
		{
			mLast->calculateSegmentDirection(mCurrentDirection, mVerticalDirection);
		}

		if (Game::getStaticInstance()->getStateOfGame()) 
		{

			// Move the unit based on boundaries and units
			pivotCentipedeBasedOnPosition();
			pivotCentipedeBasedOnUnitCollisions();
			moveCentipedeSegment();

			mTimeElapsed = Game::getStaticInstance()->getCentipedeSpeed();
		}
	}

	// Check for other collisions
	checkForCollision();
}





// This function checks for any collision with other units
void CentipedeSegment::checkForCollision() 
{
	for (int i = 0; i < Game::getStaticInstance()->getUnitManager()->getSize(); i++)
	{
		if (Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mX > mCurrentLocation.mX - Game::getStaticInstance()->getCentipedeDimensions().mX &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mX < mCurrentLocation.mX + Game::getStaticInstance()->getCentipedeDimensions().mX &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY > mCurrentLocation.mY - Game::getStaticInstance()->getCentipedeDimensions().mY &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY < mCurrentLocation.mY + Game::getStaticInstance()->getCentipedeDimensions().mY
			)
		{
			if (Game::getStaticInstance()->getUnitManager()->getUnit(i)->getCurrentUnitType() == BULLET)
			{
				// Destroy the segment and create a Mushroom in its place
				Game::getStaticInstance()->getUnitManager()->getUnit(i)->destroyThisGameObject(Game::getStaticInstance()->getUnitManager());
				Game::getStaticInstance()->createMushroom(Vector2(mCurrentLocation.mX, mCurrentLocation.mY));
				Game::getStaticInstance()->getUnitManager()->destroyCentipede(this);
				Game::getStaticInstance()->addToScore(Game::getStaticInstance()->getScoringValueForCentipedeSegment());
				return;
			}
		}
	}
	if (Game::getStaticInstance()->getUnitManager()->getPlayer() != nullptr)
	{
		// If yes, s the segment colliding with the player?
		if (Game::getStaticInstance()->getUnitManager()->getPlayer()->getLocation().mX >= mCurrentLocation.mX - Game::getStaticInstance()->getCentipedeDimensions().mX &&
			Game::getStaticInstance()->getUnitManager()->getPlayer()->getLocation().mX <= mCurrentLocation.mX + Game::getStaticInstance()->getCentipedeDimensions().mX &&
			Game::getStaticInstance()->getUnitManager()->getPlayer()->getLocation().mY >= mCurrentLocation.mY - Game::getStaticInstance()->getCentipedeDimensions().mY &&
			Game::getStaticInstance()->getUnitManager()->getPlayer()->getLocation().mY <= mCurrentLocation.mY + Game::getStaticInstance()->getCentipedeDimensions().mY
			)
		{
			// If yes, then take away a life
			Game::getStaticInstance()->endLife();
		}
	}
}





// This function changes the direction by a given value
void CentipedeSegment::changeDirection(Direction newDirection) 
{
	mCurrentDirection = newDirection;
}





// This function changes the direction of the centipede to a given direction
void CentipedeSegment::calculateSegmentDirection(Direction newDirection, Direction newVerticalDirection)
{
	// Set the vertical direction to whatever the head's vertical direction is
	mVerticalDirection = newVerticalDirection;

	if (mLast != nullptr) 
	{
		mLast->calculateSegmentDirection(mCurrentDirection, mVerticalDirection);
	}

	// Check for Collisions
	checkForCollision();

	// Change the direction and move appropriately
	changeDirection(newDirection);
	moveCentipedeSegment();
}





// This function updates the animation of the given segment
void CentipedeSegment::updateAnimations() 
{
	if (mLast != nullptr)
	{
		mLast->updateAnimations();
	}

	// The following code updates the current frame of the animation
	if (mCurrentAnimations.size() != 0) 
	{
		mCurrentAnimations[mCurrentAnimationIndex]->updateSprite();
	}
}





// This function helps to move the Centipede segment by a certain amount in a given direction
void CentipedeSegment::moveCentipedeSegment() 
{
	switch (mCurrentDirection)
	{
	case UP:
		moveToPosition(Vector2(mCurrentLocation.mX, mCurrentLocation.mY - Game::getStaticInstance()->getCentipedeDimensions().mY));
		break;
	case DOWN:
		moveToPosition(Vector2(mCurrentLocation.mX, mCurrentLocation.mY + Game::getStaticInstance()->getCentipedeDimensions().mY));
		break;
	case LEFT:
		moveToPosition(Vector2(mCurrentLocation.mX - Game::getStaticInstance()->getCentipedeDimensions().mX, mCurrentLocation.mY));
		break;
	case RIGHT:
		moveToPosition(Vector2(mCurrentLocation.mX + Game::getStaticInstance()->getCentipedeDimensions().mX, mCurrentLocation.mY));
		break;
	default:
		break;
	}
}





// This function is meant to change the Centipede's direction based on it's position in the level
void CentipedeSegment::pivotCentipedeBasedOnPosition() 
{
	// Has the segment reached the end of the screen and it is already not moving up or down?
	if ((mCurrentLocation.mX <= 0 || mCurrentLocation.mX >= Game::getStaticInstance()->getDisplayDimensions().mX - Game::getStaticInstance()->getCentipedeDimensions().mX) && mCurrentDirection != DOWN && mCurrentDirection != UP)
	{
		// If the Head is at either end of the Vertical bounds that it an
		// move, invert the direction it can go when it shift rows
		if (mCurrentLocation.mY >= Game::getStaticInstance()->getDisplayDimensions().mY - Game::getStaticInstance()->getCentipedeDimensions().mY)
		{
			mVerticalDirection = UP;
		}
		else if (mCurrentLocation.mY <= Game::getStaticInstance()->getCentipedeDimensions().mY)
		{
			mVerticalDirection = DOWN;
		}

		// Change directions to shift rows
		changeDirection(mVerticalDirection);
	}
	// Has there been up or down movement triggered by colliding with a mushroom
	else if (mHasBeenMovedByMushroom)
	{
		// Was the last horizontal direction left?
		if (mCurrentLocation.mX <= 0)
		{
			// Then change direction to go left and have the next segment do that as well
			changeDirection(RIGHT);
			mLastHorizontalDirection = LEFT;
		}
		// Was the last horizontal direction left?
		else if (mCurrentLocation.mX >= Game::getStaticInstance()->getDisplayDimensions().mX - Game::getStaticInstance()->getCentipedeDimensions().mX)
		{
			changeDirection(LEFT);
			mLastHorizontalDirection = RIGHT;
		}
		// Was the last horizontal direction left?
		else if (mLastHorizontalDirection == LEFT)
		{
			// Then change direction to go left and have the next segment do that as well
			changeDirection(LEFT);
			mLastHorizontalDirection = RIGHT;
		}
		// Was the last horizontal direction left?
		else if (mLastHorizontalDirection == RIGHT)
		{
			// Then change direction to go right and have the next segment do that as well
			changeDirection(RIGHT);
			// Change the last direction to right
			mLastHorizontalDirection = LEFT;
		}
		mHasBeenMovedByMushroom = false;
	}
	else if (mCurrentDirection == DOWN || mCurrentDirection == UP)
	{
		// Was the last horizontal direction left?
		if (mCurrentLocation.mX <= 0)
		{
			// Then change direction to go left and have the next segment do that as well
			changeDirection(RIGHT);
			mLastHorizontalDirection = LEFT;
		}
		// Was the last horizontal direction left?
		else
		{
			changeDirection(LEFT);
			mLastHorizontalDirection = RIGHT;
		}

	}
}





// This function is meant to check for any Collisions with any Mushrooms within the area and
// will return a boolean to represent if any mushrooms are colliding with the unit from a given position
bool CentipedeSegment::checkForAnyMushroomCollisions( Vector2 posToBeChecked ) 
{
	for (int i = 0; i < Game::getStaticInstance()->getUnitManager()->getSize(); i++)
	{
		if (Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mX > posToBeChecked.mX - Game::getStaticInstance()->getCentipedeDimensions().mX &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mX < posToBeChecked.mX + Game::getStaticInstance()->getCentipedeDimensions().mX &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY > posToBeChecked.mY - Game::getStaticInstance()->getCentipedeDimensions().mY &&
			Game::getStaticInstance()->getUnitManager()->getUnit(i)->getLocation().mY < posToBeChecked.mY + Game::getStaticInstance()->getCentipedeDimensions().mY
			)
		{
			// Is the Colliding Unit a Mushroom?
			if (Game::getStaticInstance()->getUnitManager()->getUnit(i)->getCurrentUnitType() == MUSHROOM)
			{
				return true;
			}

		}

	}
	// If there are no colliding mushrooms, return false
	return false;
}





// This function moves a unit based on non-boundary units
void CentipedeSegment::pivotCentipedeBasedOnUnitCollisions() 
{
	Vector2 tempDirection = mCurrentLocation;

	// The following code now checks if the predicted direction is thesable to do
	switch (mCurrentDirection)
	{
	case UP:
		tempDirection.mY = mCurrentLocation.mY - Game::getStaticInstance()->getCentipedeDimensions().mY;
		break;
	case DOWN:
		tempDirection.mY = mCurrentLocation.mY + Game::getStaticInstance()->getCentipedeDimensions().mY;
		break;
	case LEFT:
		tempDirection.mX = mCurrentLocation.mX - Game::getStaticInstance()->getCentipedeDimensions().mX;
		break;
	case RIGHT:
		tempDirection.mX = mCurrentLocation.mX + Game::getStaticInstance()->getCentipedeDimensions().mX;
		break;
	default:
		break;
	}

	if (checkForAnyMushroomCollisions(tempDirection))
	{
		// If the Head is at either end of the Vertical bounds that it an
				// move, invert the direction it can go when it shift rows
		if (mCurrentLocation.mY >= Game::getStaticInstance()->getDisplayDimensions().mY - Game::getStaticInstance()->getCentipedeDimensions().mY)
		{
			mVerticalDirection = UP;
		}
		else if (mCurrentLocation.mY <= 5)
		{
			mVerticalDirection = DOWN;
		}

		// Change directions to shift rows
		changeDirection(mVerticalDirection);
		mHasBeenMovedByMushroom = true;
	}

	tempDirection = mCurrentLocation;

	// The following code now checks if the predicted direction is thesable to do
	switch (mCurrentDirection)
	{
	case UP:
		tempDirection.mY = mCurrentLocation.mY - Game::getStaticInstance()->getCentipedeDimensions().mY;
		break;
	case DOWN:
		tempDirection.mY = mCurrentLocation.mY + Game::getStaticInstance()->getCentipedeDimensions().mY;
		break;
	case LEFT:
		tempDirection.mX = mCurrentLocation.mX - Game::getStaticInstance()->getCentipedeDimensions().mX;
		break;
	case RIGHT:
		tempDirection.mX = mCurrentLocation.mX + Game::getStaticInstance()->getCentipedeDimensions().mX;
		break;
	default:
		break;
	}


	// The following code rechecks again if the predicted direction has an object again
	if (checkForAnyMushroomCollisions(tempDirection))
	{
		// Was the last horizontal direction left?
		if (mLastHorizontalDirection == LEFT)
		{
			// Then change direction to go left and have the next segment do that as well
			changeDirection(LEFT);
			mLastHorizontalDirection = RIGHT;
		}
		// Was the last horizontal direction left?
		else if (mLastHorizontalDirection == RIGHT)
		{
			// Then change direction to go right and have the next segment do that as well
			changeDirection(RIGHT);
			// Change the last direction to right
			mLastHorizontalDirection = LEFT;
		}
		mHasBeenMovedByMushroom = false;
	}
}





// This function gets the next segment in the Centipede
CentipedeSegment * CentipedeSegment::getNextSegment() 
{
	return mNext;
}





// This function get the previous segment in the Centipede
CentipedeSegment * CentipedeSegment::getLastSegment() 
{
	return mLast;
}