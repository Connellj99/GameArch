#include "UnitManager.h"



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
Unit UnitManager::getUnit( int index ) 
{
	return *mUnits[index];
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
	for ( int i = 0, max = mUnits.size(); i < max; i++ )
	{
		mUnits[i]->draw();
	}
}





// This function gets the size of the units member vector,
// which stores all of the units of the game
int UnitManager::getSize() 
{
	return mUnits.size();
}





// This function removes all of the units within the unit list
void UnitManager::removeAllUnits() 
{
	for ( int i = 0, max = mUnits.size(); i < max; i++ )
	{
		delete mUnits[i];
	}
}