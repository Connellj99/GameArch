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





// This function creates a unit at a given position and also adds
// a animation to said unit
void UnitManager::createUnit( Vector2 newPos )
{
	mUnits.push_back( new Unit(newPos) );
}





// This function creates the question block unit at a given position
void UnitManager::createQuestionBlock(Vector2 newPos) 
{
	mUnits.push_back(new QuestionBlock(newPos));
}





// This function creates the brick block unit at a given position
void UnitManager::createBrickBlock(Vector2 newPos) 
{
	mUnits.push_back(new BrickBlock(newPos));
}





// This function creates a Goomba unit at a given position
void UnitManager::createGoomba(Vector2 newPos) 
{
	mUnits.push_back(new Goomba(newPos));
}





// This function creates a Prop at a given position
void UnitManager::createProp(Vector2 newPos, Animation * newAnim) 
{
	mProps.push_back((new Prop(newPos, newAnim)));
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
}





// This function calls all units in the game to draw
// themselves to the back buffer
void UnitManager::draw() 
{
	for (int i = 0, max = mProps.size(); i < max; i++)
	{
		mProps[i]->draw();
	}

	if (mPlayer != nullptr) 
	{
		mPlayer->draw();
	}

	for ( int i = 0, max = mUnits.size(); i < max; i++ )
	{
		mUnits[i]->draw();
	}
}





// This function moves the Player Unit to a given position
void UnitManager::movePlayer(Vector2 newPos) 
{
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
	for (int i = 0, max = mProps.size(); i < max; i++)
	{
		delete mProps[i];
	}
	mUnits.clear();
}





// This function creates the Player Unit at a given position
void UnitManager::createPlayer(Vector2 newPos) 
{
	mPlayer = new Player(newPos);
}





// This function gets the current object of the Player Unit
Player * UnitManager::getPlayer() 
{
	return mPlayer;
}