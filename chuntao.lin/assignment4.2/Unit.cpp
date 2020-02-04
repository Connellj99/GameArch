#include "Unit.h"
#include "Game.h"

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
	for (Animation* anim : mpCurrentAnimations)
	{
		delete anim;
	}
}



// This function sets the animation(s) for the unit
void Unit::setAnimation( Animation * newAnimation ) 
{
	mpCurrentAnimations.push_back( newAnimation );
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
	mpCurrentAnimations[mCurrentAnimationIndex]->update( newTimeBetweenFrames );
}





// This function adjusts the animation speed for al animations
void Unit::changeAnimationSpeeds( double speedsToBeChanged ) 
{
	for (int i = 0, max = mpCurrentAnimations.size(); i < max; i++) 
	{
		mpCurrentAnimations[i]->adjustCurrentSpeed( speedsToBeChanged );
	}
}

void Unit::toggleAnimationSpeeds()
{
	for (int i = 0, max = mpCurrentAnimations.size(); i < max; i++)
	{
		mpCurrentAnimations[i]->toggleCurrentSpeed();
	}
}





// This function gets the current animation that is being played
Animation * Unit::getCurrentAnimation() 
{
	return mpCurrentAnimations[mCurrentAnimationIndex];
}




// This function draws the unit's sprite to the screen
void Unit::draw() 
{
	Game::getInstance()->getCurrentSystem()->getGraphicsSystem().draw( mCurrentLocation, *mpCurrentAnimations[mCurrentAnimationIndex]->getCurrentSprite(), DEFAULT_SCALING_VALUE );
}

Vector2 Unit::returnLocation()
{
	return mCurrentLocation;
}

void Unit::cleanUnitAndSprites()
{
	for (int i = 0; i < (int)mpCurrentAnimations.size(); i++)
	{
		mpCurrentAnimations[i]->cleanAnimation();
	}
}

void Unit::cleanUnit()
{
	for (int i = 0; i < (int)mpCurrentAnimations.size(); i++)
	{
		delete mpCurrentAnimations[i];
	}
}

// This function swaps the current animation that is being played
void Unit::swapAnimation() 
{

	// The following code determines if the current animation is the
	// last animation in the animations vector. If it is, cycle back to 
	// the start of the vector other wise just go to the next animation.
	if ( mCurrentAnimationIndex == mpCurrentAnimations.size() - 1 )
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