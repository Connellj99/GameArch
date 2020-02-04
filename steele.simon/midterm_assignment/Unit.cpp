#include "Unit.h"
#include "Game.h"




// This function is the default constructor for this class
Unit::Unit()
{
	mCurrentLocation = Vector2(0, 0);
	mCurrentAnimationIndex = 0;
	isAnimationStopped = false;
	mUnitType = NONE;
}





// This constructor is for if the user wants to 
// initialize the position of a sprite
Unit::Unit( Vector2 newPos ) 
{
	mCurrentLocation = newPos;
	mCurrentAnimationIndex = 0;
	isAnimationStopped = false;
	mUnitType = NONE;
}





// This constructor creates the Unit at a given position 
// and adds an animation to said Unit as well
Unit::Unit(Vector2 newPosition, Animation * newAnimation) 
{
	mCurrentLocation = newPosition;
	setAnimation(*newAnimation);
	isAnimationStopped = false;
	mUnitType = NONE;
}





// This function is the destructor for this class
Unit::~Unit()
{
	for (int i = 0, max = mCurrentAnimations.size(); i < max; i++) 
	{
		mCurrentAnimations[i]->cleanupAnimation();
		delete mCurrentAnimations[i];
	}
}





// This function sets the animation(s) for the unit
void Unit::setAnimation( Animation & newAnimation ) 
{
	mCurrentAnimations.push_back(new Animation(newAnimation) );
}





// This function moves the Unit to the given mouse position
void Unit::moveToMousePosition( Vector2 newMousePos )
{
	Vector2 newPos = Vector2( newMousePos.mX - getCurrentAnimation()->getCurrentSprite()->getDisplacement().mX, newMousePos.mY - getCurrentAnimation()->getCurrentSprite()->getDisplacement().mY );
	mCurrentLocation = newPos;
}





// This function moves the Unit to a given position
void Unit::moveToPosition(Vector2 newPos) 
{
	mCurrentLocation = newPos;
}





// This function switches the state of the Unit animation to either play or stop
void Unit::switchStateOfAnimation()
{
	if (isAnimationStopped) 
	{
		isAnimationStopped = false;
	}
	else 
	{
		isAnimationStopped = true;
	}
}





// This function is the default update for this class
void Unit::update( double newTimeBetweenFrames )
{
	if (isAnimationStopped == false) 
	{
		// The following code updates the current frame of the animation
		mCurrentAnimations[mCurrentAnimationIndex]->update(newTimeBetweenFrames);
	}
}





// This function adjusts the animation speed for al animations
void Unit::changeAnimationSpeeds( double speedsToBeChanged ) 
{
	for (int i = 0, max = mCurrentAnimations.size(); i < max; i++) 
	{
		mCurrentAnimations[i]->adjustCurrentSpeed( speedsToBeChanged );
	}
}





// This function gets the current animation that is being played
Animation * Unit::getCurrentAnimation() 
{
	return mCurrentAnimations[mCurrentAnimationIndex];
}




// This function draws the unit's sprite to the screen
void Unit::draw() 
{
	if (mCurrentAnimations.size() != 0) 
	{
		Game::getStaticInstance()->getCurrentSystem()->getGraphicsSystem().draw(mCurrentLocation, *mCurrentAnimations[mCurrentAnimationIndex]->getCurrentSprite(), DEFAULT_SCALING_VALUE);
	}
}





// This function swaps the current animation that is being played
void Unit::swapAnimation() 
{

	// The following code determines if the current animation is the
	// last animation in the animations vector. If it is, cycle back to 
	// the start of the vector other wise just go to the next animation.
	if ( mCurrentAnimationIndex == mCurrentAnimations.size() - 1 )
	{
		mCurrentAnimationIndex = 0;
	}
	else 
	{
		mCurrentAnimationIndex++;
	}

}





// This function checks if the current unit is visible
bool Unit::isVisible() 
{
	// The following code checks if the current unit is within the current display window
	return mCurrentLocation.mX > 0 && mCurrentLocation.mX < Game::getStaticInstance()->getDisplayDimensions().mX && mCurrentLocation.mY > 0 && mCurrentLocation.mY < Game::getStaticInstance()->getDisplayDimensions().mX;
}





// This function destroys the Unit and then calls UnitManager to remove it from the Unit List
void Unit::destroyThisGameObject(UnitManager * manager) 
{
	for (int i = 0; i < manager->getSize(); i++) 
	{
		if (manager->getUnit(i) == this) 
		{
			manager->destroyUnit(i);
			break;
		}
	}
}





// This function gets the current location of the Unit
Vector2 Unit::getLocation() 
{
	Vector2 temp = Vector2(mCurrentLocation.mX, mCurrentLocation.mY);
	return temp;
}





// This function gets the current Unit Type of the Unit
UnitTypes Unit::getCurrentUnitType() 
{
	return mUnitType;
}