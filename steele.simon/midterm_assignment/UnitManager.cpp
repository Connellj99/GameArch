#include "UnitManager.h"
#include "Game.h"


// This function is the default constructor for the class
UnitManager::UnitManager()
{

}





// This function is the destructor for the class
UnitManager::~UnitManager()
{
	removeAllUnits();
}





// This function gets a specific unit from the units vector
// Based on a given index
Unit * UnitManager::getUnit( int index ) 
{
	return mUnits[index];
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





// This function creates a unit at a given position and also adds
// a animation to said unit
void UnitManager::createUnit( Vector2 newPos )
{
	mUnits.push_back( new Unit(newPos) );
}





// This function creates a bullet object at a given position
void UnitManager::createBullet(Vector2 newPos) 
{
	mUnits.push_back( new Bullet(newPos) );
}





// This function creates a mushroom object at a given position
void UnitManager::createMushroom(Vector2 newPos) 
{
	mUnits.push_back(new Mushroom(newPos));
}





// This function creates a Centipede segment at a given position
void UnitManager::createCentipedeSegment(Vector2 newPos) 
{
	mUnits.push_back(new CentipedeSegment(newPos));
}





// This functions adds a given animation to a unit based on a given index
void UnitManager::addAnimation( int index, Animation & newAnim ) 
{
	mUnits[index]->setAnimation(newAnim);
}





// This functions adds a given animation to a unit based on a given index
void UnitManager::addPlayerAnimation(Animation & newAnim)
{
	mPlayer->setAnimation(newAnim);
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





// This function swaps the current animation of a 
// unit based on a given index
void UnitManager::swapPlayerAnimations()
{
	mPlayer->swapAnimation();
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
	if (mPlayer != nullptr) 
	{
		mPlayer->update(timeBetweenFrames);
	}

	for ( int i = 0, max = mUnits.size(); i < max; i++ ) 
	{
		mUnits[i]->update( timeBetweenFrames );
		max = mUnits.size();
	}

	// The following code updates all of the positions of the
	// Centipede segments within each Centipede
	for (int i = 0, max = mCentipedes.size(); i < max; i++) 
	{
		if (Game::getStaticInstance()->getStateOfGame()) 
		{
			mCentipedes[i]->update(timeBetweenFrames);
			max = mCentipedes.size();
		}
	}
}





// This function calls all units in the game to draw
// themselves to the back buffer
void UnitManager::draw() 
{
	if (mPlayer != nullptr) 
	{
		mPlayer->draw();
	}

	for ( int i = 0, max = mUnits.size(); i < max; i++ )
	{
		mUnits[i]->draw();
	}

	for (int i = 0, max = mCentipedes.size(); i < max; i++) 
	{
		mCentipedes[i]->draw();
	}
}





// This function moves the Player Unit to a given position
void UnitManager::movePlayer(Vector2 newPos) 
{
	// Is this desired position within the bounds the player can move?
	if (newPos.mY >= Game::getStaticInstance()->getBoundsOfPlayer().mY)
	{
		// If yes, move the Player to that position
		mPlayer->moveToMousePosition(newPos);
	}
	else 
	{
		// If no, move the Player to that position but restrict
		// it's Y to the top of the Y moving bounds
		mPlayer->moveToMousePosition(Vector2(newPos.mX, Game::getStaticInstance()->getBoundsOfPlayer().mY));
	}
}





// This function gets the size of the units member vector,
// which stores all of the units of the game
int UnitManager::getSize() 
{
	return mUnits.size();
}





// This function removes all of the units within the unit list and erases the unit vector
void UnitManager::removeAllUnits() 
{
	delete mPlayer;
	mPlayer = nullptr;
	for ( int i = 0, max = mUnits.size(); i < max; i++ )
	{
		delete mUnits[i];
	}
	mUnits.clear();

	for (int i = 0, max = mCentipedes.size(); i < max; i++)
	{
		delete mCentipedes[i];
	}
	mCentipedes.clear();
}





// This function creates the Player Unit at a given position
void UnitManager::createPlayer(Vector2 newPos) 
{
	mPlayer = new Player(newPos);
}





// This function creates a Centipede at a given position with a given amount of values
void UnitManager::createCentipede(Vector2 newPos, int amountOfSegments) 
{
	mCentipedes.push_back(new CentipedeManager());

	// Create and add the head segment to the Centipede
	mCentipedes[mCentipedes.size() - 1]->addSegmentToCentipede(new CentipedeSegment(Vector2(newPos.mX, newPos.mY)));

	// The following code creates a Centipede segment for the amount of segments given
	for (int i = 1; i < amountOfSegments; i++) 
	{
		mCentipedes[mCentipedes.size() - 1]->addSegmentToCentipede(new CentipedeSegment(Vector2(newPos.mX - (i * 32), newPos.mY)));
	}

	mCentipedes[mCentipedes.size() - 1]->changeHeadAnimation();
}





// This function destroys the current centipede by taking a segment out and
// then splitting the centipede in two
void UnitManager::destroyCentipede(CentipedeSegment * segmentToBeDestroyed) 
{
	for (int i = 0, max = mCentipedes.size(); i < max; i++) 
	{
		mCentipedes[i]->removeSegmentOfCentipede(segmentToBeDestroyed);
	}
	Game::getStaticInstance()->deductNumOfSegments();
}





// This function gets the current object of the Player Unit
Player * UnitManager::getPlayer() 
{
	return mPlayer;
}





// This function splits a given centipede and creates a new centipede with a given head
void UnitManager::splitCentipede(CentipedeSegment * newHead) 
{
	mCentipedes.push_back(new CentipedeManager());
	mCentipedes[mCentipedes.size() - 1]->addSegmentToCentipede(newHead);
	mCentipedes[mCentipedes.size() - 1]->changeHeadAnimation();
	mCentipedes[mCentipedes.size() - 1]->resetAnimations();
}





// This function gets a Centipedes at a given index and returns it
CentipedeManager* UnitManager::getCentipede(int elementTheCentipedeIsAt) 
{
	return mCentipedes[elementTheCentipedeIsAt];
}





// This function returns the size of the centipede vector
int UnitManager::getCentipedeVectorSize() 
{
	return mCentipedes.size();
}