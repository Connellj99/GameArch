#include "UnitManager.h"

// This function is the default constructor for the class
UnitManager::UnitManager()
{
	mTargetTime = 60;
	mTimeElapsed = mTargetTime;
	mCurrentIndex = 0;
}


// This function is the destructor for the class
UnitManager::~UnitManager()
{
	removeAndDestroyAllUnits();
}





// This function gets a specific unit from the units vector
// Based on a given index
Unit UnitManager::getUnit( int index ) 
{
	return *mUnits[index];
}

Vector2 UnitManager::getUnitPos(int index)
{
	return mUnits[index]->mCurrentLocation;
}


// This function deletes any units that are within a given point
void UnitManager::deleteUnitFromGivenPoint( Vector2 newPos ) 
{
	// Vector2's
	Vector2 unitPos;


	// The following code iterates through the vector of all units
	// and checks if the unit is within the area of deletion
	for ( int i = 0, max = mUnits.size(); i < max; i++ ) 
	{
		// Get the position of the unit
		unitPos = mUnits[i]->mCurrentLocation;

		// Is the unit's position within the mouse position and its corresponding radius?
		if ( unitPos.mX <= newPos.mX + CLICK_DIMENSIONS.mX &&
			 unitPos.mX >= newPos.mX - CLICK_DIMENSIONS.mX &&
			 unitPos.mY <= newPos.mY + CLICK_DIMENSIONS.mY &&
			 unitPos.mY >= newPos.mY - CLICK_DIMENSIONS.mY )
		{
			// If yes, then destroy the unit
			destroyUnit(i);

			// Reset for loop because size of vector has changed
			i = 0;
			max = mUnits.size();
		}
	}
}

void UnitManager::setFruitStatus(bool newFruitStatus)
{
	mEatFruit = newFruitStatus;
}

void UnitManager::setPowerUpStatus(bool newPowerUpStatus)
{
	mEatPowerUp = newPowerUpStatus;
}

void UnitManager::setCrashStatus(bool newWallStatus)
{
	mCrashedWall = newWallStatus;
}




//Once the bools are set to true, they return a number, which will be put into another function that has a switch
int UnitManager::getPowerUpTypeStatus()
{
	if (mBonusPt == true)
	{
		return 0;
	}
	if(mSlowDown == true)
	{
		return 1;
	}
	if (mSpeedUp == true)
	{
		return 2;
	}
	return -1;//return abritrary number
}

//Spawn snake if you wanted two types of animations
void UnitManager::spawnSnake(int numUnitsWanted,Animation* animationOne, Animation* animationTwo)
{
	//Create segments of the snake
	for (int i = 0; i < numUnitsWanted; i++)
	{
		createUnit(Vector2((800 / 2) - (20*i), 600 / 2));

		// add both animations to the unit, the dean and smurf.
		addAnimation(getSize() - 1, *animationOne);
		addAnimation(getSize() - 1, *animationTwo);
	}
}

//Spawn snake for one animation, in my case this is used.
void UnitManager::spawnSnake(int numUnitsWanted, Animation * animationOne)
{
	//Create segments of the snake
	for (int i = 0; i < numUnitsWanted; i++)
	{
		createUnit(Vector2((800 / 2) - (15 * i), 600 / 2));

		// add both animations to the unit, the dean and smurf.
		addAnimation(getSize() - 1, *animationOne);
	}
}

void UnitManager::resetEating()
{
	mEatFruit = false;
}

// This function creates a unit at a given position and also adds
// a animation to said unit
void UnitManager::createUnit( Vector2 newPos )
{
	mUnits.push_back( new Unit(newPos) );
}

//This function will call the create unit function(adding to the vector), and then add animations  to one single new unit/snake segment
void UnitManager::increaseLength(Vector2 newPos,Animation* animationOne, Animation* animationTwo)
{
	createUnit(Vector2(newPos.mX, newPos.mY));
	addAnimation(getSize() - 1, *animationOne);
	addAnimation(getSize() - 1, *animationTwo);
}

void UnitManager::increaseLength(Vector2 newPos, Animation * animationOne)
{
	createUnit(Vector2(newPos.mX, newPos.mY));
	addAnimation(getSize() - 1, *animationOne);
}





// This functions adds a given animation to a unit based on a given index
void UnitManager::addAnimation( int index, Animation & newAnim ) 
{
	mUnits[index]->setAnimation(newAnim);
}





// This function destroys and deletes a unit from the
// vector based on a given index
void UnitManager::destroyUnit( int index ) 
{
	delete mUnits[index];
	mUnits.erase( mUnits.begin() + index );
}





// This function swaps the current animation of a 
// unit based on a given index
void UnitManager::swapAnimations( int index ) 
{
	// Is the given index within bounds?
	if (index > -1 && index < getSize()) 
	{
		// If yes, then swap the animation at the given index
		mUnits[index]->swapAnimation();
	}
}





// This function plays or stops all animations for all units
void UnitManager::playOrStopUnitAnimations() 
{
	for ( int i = 0, max = mUnits.size(); i < max; i++ ) 
	{
		mUnits[i]->switchStateOfAnimation();
	}
}





// This function calls the update function for all units in the game and
// also passed to all units the given time that has passed since last update
void UnitManager::update( double timeBetweenFrames ) 
{
	for ( int i = 0, max = mUnits.size(); i < max; i++ ) 
	{
		mUnits[i]->update( timeBetweenFrames );
	}
}





// This function calls all units in the game to draw
// themselves to the back buffer
void UnitManager::draw() 
{
	//draw units from last index to first. This is to make
	//sure that the head is visible and not behind anything
	if (getSize() > 1)
	{
		for (int i = mUnits.size() - 1; i > 0; i--)
		{
			mUnits[i]->draw("player");
		}
	}
	else if(getSize() == 1)
	{
		mUnits[0]->draw("player");
	}

}

void UnitManager::checkPositionFromBorderWalls()
{
	if (mUnits[0]->mCurrentLocation.mX <= 3 )//left walls
	{
		removeAndDestroyAllUnits();
	}
	else if (mUnits[0]->mCurrentLocation.mX >= 766)//right walls
	{
		removeAndDestroyAllUnits();
	}
	else if (mUnits[0]->mCurrentLocation.mY <= 0)//top walls
	{
		removeAndDestroyAllUnits();
	}
	else if (mUnits[0]->mCurrentLocation.mY >= 580)//down walls
	{
		removeAndDestroyAllUnits();
	}
	
}

//FOR SOME REASON THIS ONE LIKES TO SAY HEAD AND NEXT UNIT SOMETIMES ARE THE SAME POSITION
void UnitManager::checkPositionFromBody()
{
	//checking head to body collisions.
	for (int i = 1; i < (int)mUnits.size(); i++)
	{
		/*if (mUnits[0]->mCurrentLocation.mX == mUnits[i]->mCurrentLocation.mX &&
			mUnits[0]->mCurrentLocation.mY == mUnits[i]->mCurrentLocation.mY)

		{
			removeAndDestroyAllUnits();
		}*/
	}
}

//This function checks to see if the head comes into range with the food/grow good
void UnitManager::checkPositionFromFood(Vector2 foodPos)
{
	if (mUnits[0]->mCurrentLocation.mX <= foodPos.mX + 15 &&
		mUnits[0]->mCurrentLocation.mX >= foodPos.mX - 15 &&
		mUnits[0]->mCurrentLocation.mY <= foodPos.mY + 15 &&
		mUnits[0]->mCurrentLocation.mY >= foodPos.mY - 15)
	{
		setFruitStatus(true);
	}
}

//This function checks to see if the head hits any of the walls in the manager
void UnitManager::checkPositionFromWalls(WallManager* wallManage)
{
	//check the position of the head to all the spawned walls/barricades
	if (mUnits.size() != 0)
	{
		for (int i = 0; i < wallManage->getSize(); i++)
		{
			if (mUnits[0]->mCurrentLocation.mX <= wallManage->getWallPos(i).mX + 15 &&
				mUnits[0]->mCurrentLocation.mX >= wallManage->getWallPos(i).mX - 15 &&
				mUnits[0]->mCurrentLocation.mY <= wallManage->getWallPos(i).mY + 15 &&
				mUnits[0]->mCurrentLocation.mY >= wallManage->getWallPos(i).mY - 15)
			{
				removeAndDestroyAllUnits();
				break;
			}
		}
	}
	
}


//This function checks if the head hits any item from powerup manager
void UnitManager::checkPositionFromPowerUps(PowerUpManager* powerUpManage)
{
	//check the position of the head to all the spawned walls/barricades
	if (mUnits.size() != 0)
	{
		for (int i = 0; i < powerUpManage->getSize(); i++)
		{
			if (mUnits[0]->mCurrentLocation.mX <= powerUpManage->getPos(i).mX + 10 &&
				mUnits[0]->mCurrentLocation.mX >= powerUpManage->getPos(i).mX - 10 &&
				mUnits[0]->mCurrentLocation.mY <= powerUpManage->getPos(i).mY + 10 &&
				mUnits[0]->mCurrentLocation.mY >= powerUpManage->getPos(i).mY - 10)
			{
				if (powerUpManage->getUnitType(i) == "bonusPt")
				{
					setPowerUpStatus(true);
					mBonusPt = true;
					powerUpManage->destroyPowerUp(i);
				}
				else	if (powerUpManage->getUnitType(i) == "slow")
				{
					setPowerUpStatus(true);
					mSlowDown = true;
					powerUpManage->destroyPowerUp(i);
				}
				else	if (powerUpManage->getUnitType(i) == "fast")
				{
					setPowerUpStatus(true);
					mSpeedUp = true;
					powerUpManage->destroyPowerUp(i);
				}
				break;
			}
		}
	}
}

void UnitManager::moveUnitsLeft(int spd,double framesPassed)
{

	mTimeElapsed -= framesPassed;
	mTimeElapsed -= spd;//with the spd, it basically reduces the time elapsed at a faster rate, which results in a fast movement

	if (mCurrentIndex >= (int)mUnits.size() - 1)
	{
		mCurrentIndex = 0;
	}

	if (mTimeElapsed <= 0.0)//if the time elapsed is now 0, run
	{

		Vector2 oldPos = Vector2(mUnits[mCurrentIndex]->mCurrentLocation.mX , mUnits[mCurrentIndex]->mCurrentLocation.mY);//set the old position
		Vector2 newPos = Vector2(mUnits[mCurrentIndex]->mCurrentLocation.mX - (25), mUnits[mCurrentIndex]->mCurrentLocation.mY);//with the new

		if (getSize() > 1)//if there is more than one unit
		{
			mUnits[mCurrentIndex]->setNewPos(newPos);//set the current index unit/segment with the new position
			mUnits[mCurrentIndex + 1]->setNewPos(oldPos);//set the next unit/segment with the old position
			mTimeElapsed = mTargetTime;//reset the time
			mCurrentIndex += 1;//move Up the index
		}
		else if (getSize() == 1)//if there  is 1 unit
		{
			mUnits[mCurrentIndex]->mCurrentLocation = newPos;
			mTimeElapsed = mTargetTime;
		}

		checkPositionFromBody();
	}
	
}

void UnitManager::moveUnitsRight(int spd, double framesPassed)
{

	mTimeElapsed -= framesPassed;
	mTimeElapsed -= spd;


	if (mCurrentIndex >= (int)mUnits.size() - 1)
	{
		mCurrentIndex = 0;
	}

	if (mTimeElapsed <= 0.0)
	{
		Vector2 oldPos = Vector2(mUnits[mCurrentIndex]->mCurrentLocation.mX, mUnits[mCurrentIndex]->mCurrentLocation.mY);
		Vector2 newPos = Vector2(mUnits[mCurrentIndex]->mCurrentLocation.mX + (25), mUnits[mCurrentIndex]->mCurrentLocation.mY);
		if (getSize() > 1)
		{
	
			mUnits[mCurrentIndex]->setNewPos(newPos);//set the current index unit/segment with the new position
			mUnits[mCurrentIndex + 1]->setNewPos(oldPos);//set the next unit/segment with the old position
			mTimeElapsed = mTargetTime;
			mCurrentIndex += 1;
		}
		else if (getSize() == 1)//if there  is 1 unit
		{
			mUnits[mCurrentIndex]->mCurrentLocation = newPos;
			mTimeElapsed = mTargetTime;
		}
		checkPositionFromBody();
	}
}

void UnitManager::moveUnitsUp(int spd, double framesPassed)
{

	mTimeElapsed -= framesPassed;
	mTimeElapsed -= spd;


	if (mCurrentIndex >= (int)mUnits.size() - 1)
	{
		mCurrentIndex = 0;
	}

	if (mTimeElapsed <= 0.0)
	{
		Vector2 oldPos = Vector2(mUnits[mCurrentIndex]->mCurrentLocation.mX, mUnits[mCurrentIndex]->mCurrentLocation.mY);
		Vector2 newPos = Vector2(mUnits[mCurrentIndex]->mCurrentLocation.mX, mUnits[mCurrentIndex]->mCurrentLocation.mY - (25));
		if (getSize() > 1)
		{
			mUnits[mCurrentIndex]->setNewPos(newPos);//set the current index unit/segment with the new position
			mUnits[mCurrentIndex + 1]->setNewPos(oldPos);//set the next unit/segment with the old position
			mTimeElapsed = mTargetTime;
			mCurrentIndex += 1;
		}
		else if (getSize() == 1)//if there  is 1 unit
		{
			mUnits[mCurrentIndex]->mCurrentLocation = newPos;
			mTimeElapsed = mTargetTime;
		}
		checkPositionFromBody();
	}
}

void UnitManager::moveUnitsDown(int spd, double framesPassed)
{

	mTimeElapsed -= framesPassed;
	mTimeElapsed -= spd;

	if (mCurrentIndex >= (int)mUnits.size() - 1)
	{
		mCurrentIndex = 0;
	}

	if (mTimeElapsed <= 0.0)
	{
		
		Vector2 oldPos = Vector2(mUnits[mCurrentIndex]->mCurrentLocation.mX, mUnits[mCurrentIndex]->mCurrentLocation.mY);
		Vector2 newPos = Vector2(mUnits[mCurrentIndex]->mCurrentLocation.mX, mUnits[mCurrentIndex]->mCurrentLocation.mY + (25));
		if (getSize() > 1)
		{
			mUnits[mCurrentIndex]->setNewPos(newPos);//set the current index unit/segment with the new position
			mUnits[mCurrentIndex + 1]->setNewPos(oldPos);//set the next unit/segment with the old position
			mTimeElapsed = mTargetTime;
			mCurrentIndex += 1;
		}
		else if (getSize() == 1)//if there  is 1 unit
		{
			mUnits[mCurrentIndex]->mCurrentLocation = newPos;
			mTimeElapsed = mTargetTime;
		}
		checkPositionFromBody();
	}
}


// This function gets the size of the units member vector,
// which stores all of the units of the game
int UnitManager::getSize() 
{
	return mUnits.size();
}


// This function removes all of the units within the unit list
void UnitManager::removeAndDestroyAllUnits() 
{
	for ( int i = 0, max = mUnits.size(); i < max; i++ )
	{
		delete mUnits[i];
	}
	mUnits.clear();
}