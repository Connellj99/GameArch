#include "Unit.h"





// This function is the default constructor for this class
Unit::Unit()
{
	mCurrentLocation = Vector2(0, 0);
	mCurrentAnimationIndex = 0;
}





// This constructor is for if the user wants to 
// initialize the position of a sprite
Unit::Unit( Vector2 newPos ) 
{
	mCurrentLocation = newPos;
}





// This function is the destructor for this class
Unit::~Unit()
{
}





// This function sets the animation(s) for the unit
void Unit::setAnimation( Animation * newAnimation ) 
{
	mCurrentAnimations.push_back( newAnimation );
}





// This function updates the unit when the game loop executes
void Unit::moveToMousePosition( Vector2 newMousePos )
{
	Vector2 newPos = Vector2( newMousePos.mX - getCurrentAnimation()->getCurrentSprite()->getDisplacement().mX, newMousePos.mY - getCurrentAnimation()->getCurrentSprite()->getDisplacement().mY );
	mCurrentLocation = newPos;
}





// This function is the default update for this class
void Unit::update( double newTimeBetweenFrames )
{
	// The following code updates the current frame of the animation
	mCurrentAnimations[mCurrentAnimationIndex]->update( newTimeBetweenFrames );
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
	gpGameObject->getCurrentSystem()->getGraphicsSystem().draw( mCurrentLocation, *mCurrentAnimations[mCurrentAnimationIndex]->getCurrentSprite(), DEFAULT_SCALING_VALUE );
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
	return mCurrentLocation.mX > 0 && mCurrentLocation.mX < DISP_WIDTH && mCurrentLocation.mY > 0 && mCurrentLocation.mY < DISP_HEIGHT;
}