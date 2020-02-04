#include "Unit.h"
#include "Game.h"




// This function is the default constructor for this class
Unit::Unit()
{
	mCurrentLocation = Vector2(0, 0);
	mCurrentAnimationIndex = 0;
	isAnimationStopped = false;
}





// This constructor is for if the user wants to 
// initialize the position of a sprite
Unit::Unit( Vector2 newPos ) 
{
	mCurrentLocation = newPos;
	Vector2 newPos2 = Vector2(newPos.mX - Game::getStaticInstance()->getSpriteDisplacementX(), newPos.mY - Game::getStaticInstance()->getSpriteDisplacementY());
	mCurrentLocation = newPos2;
	isAnimationStopped = false;
}


Unit::Unit(Vector2 newPos, string type)
{
	mCurrentLocation = newPos;
	Vector2 newPos2 = Vector2(newPos.mX - Game::getStaticInstance()->getSpriteDisplacementX(), newPos.mY - Game::getStaticInstance()->getSpriteDisplacementY());
	mCurrentLocation = newPos2;
	isAnimationStopped = false;
	mType = type;
}


Unit::Unit(Vector2 newPos, string type,bool moved)
{
	mCurrentLocation = newPos;
	Vector2 newPos2 = Vector2(newPos.mX - Game::getStaticInstance()->getSpriteDisplacementX(), newPos.mY - Game::getStaticInstance()->getSpriteDisplacementY());
	mCurrentLocation = newPos2;
	isAnimationStopped = false;
	mType = type;
	mHasMoved = moved;
}

Unit::Unit(Vector2 newPosition, Animation * newAnimation) 
{
	mCurrentLocation = newPosition;
	setAnimation(*newAnimation);
	isAnimationStopped = false;
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





// This function updates the unit when the game loop executes
void Unit::moveToMousePosition( Vector2 newMousePos )
{
	Vector2 newPos = Vector2( newMousePos.mX - getCurrentAnimation()->getCurrentSprite()->getDisplacement().mX, newMousePos.mY - getCurrentAnimation()->getCurrentSprite()->getDisplacement().mY );
	mCurrentLocation = newPos;
}




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

void Unit::setMoveStatus(bool status)
{
	mHasMoved = status;
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
	Game::getStaticInstance()->getCurrentSystem()->getGraphicsSystem().draw( mCurrentLocation, *mCurrentAnimations[mCurrentAnimationIndex]->getCurrentSprite(), DEFAULT_SCALING_VALUE);
}

void Unit::draw(string typeName)
{
	if (typeName == "player")
	{
		Game::getStaticInstance()->getCurrentSystem()->getGraphicsSystem().draw(mCurrentLocation, *mCurrentAnimations[mCurrentAnimationIndex]->getCurrentSprite(), DEFAULT_SCALING_VALUE - 0.5);
	}
	else
		Game::getStaticInstance()->getCurrentSystem()->getGraphicsSystem().draw(mCurrentLocation, *mCurrentAnimations[mCurrentAnimationIndex]->getCurrentSprite(), DEFAULT_SCALING_VALUE - 0.2);
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