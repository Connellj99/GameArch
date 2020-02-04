#include "Animation.h"
#include "Game.h"

// This function is the default constructor for this class
Animation::Animation()
{
	mCurrentIndex = 0;
	mTargetTime = DEFAULT_SPEED;
	mTimeElapsed = mTargetTime;
}





// This constructor takes in the sprite sheet, the sprites per row and column, dimensions, and the display dimensions
// To divide the a given sprite to create an animation
Animation::Animation( GraphicsBuffer * spriteSheet, int spritesPerRow, int spritesPerColumn, Vector2 displayDimensions, Vector2 spriteDimensions )
{

	for (int i = 0; i < spritesPerRow * spritesPerColumn; i++) 
	{
		addSprite( new Sprite( new GraphicsBuffer( displayDimensions.mX, displayDimensions.mY, "GraphicsBuffer" ), Game::getStaticInstance()->getSpriteDisplacementX(), Game::getStaticInstance()->getSpriteDisplacementY(), true, spriteDimensions) );
	}

	// The following code splits a given sprite sheet up
	// and creates a graphics buffer for each of them to be drawn on and 
	// to then be added to the animation cycle
	for (int col = 0; col < spritesPerRow; col++) 
	{
		for (int row = 0; row < spritesPerColumn; row++) 
		{
			GraphicsSystem::drawFromSpriteSheet(*mListOfSprites[( spritesPerColumn * col ) + row]->getGraphicsBuffer(), Vector2( spriteSheet->getWidth() * ( double( col ) / double( spritesPerColumn ) ),
												spriteSheet->getHeight() * ( double( row ) / double( spritesPerRow ))), Vector2( 0, 0 ), *spriteSheet, spriteDimensions );
		}
	}

	mCurrentIndex = 0; // Initialize all member variables
	mTargetTime = DEFAULT_SPEED;
	mTimeElapsed = mTargetTime;
}





// This function is the destructor for this class
Animation::~Animation()
{
	if (mHasCleanedUp == false) 
	{
		// If yes, Delete all sprites in the animation clip
		for (int i = 0, max = mListOfSprites.size(); i < max; i++)
		{
			delete mListOfSprites[i];
		}
	}
}





// This function checks by frame for what sprite to draw in the animation loop
void Animation::update( double framesPassed ) 
{
	// The following code subtracts the time that has passed and if
	// enough time has passed, it will change frames
	mTimeElapsed -= framesPassed;

	if ( mTimeElapsed <= 0.0 ) 
	{
		updateSprite();
		mTimeElapsed = mTargetTime;
	}
}


// This function adds a sprite, which is determined from function call in main
void Animation::addSprite( Sprite * spriteToAdd )
{
	mListOfSprites.push_back( spriteToAdd );
}





// This function adjusts the speed of animation, which is determined from function call in main
void Animation::adjustCurrentSpeed( double speedToBeAdded )
{
	mTargetTime += speedToBeAdded;
}





// This function gets the current sprite of the animation
Sprite * Animation::getCurrentSprite() 
{
	return mListOfSprites[mCurrentIndex];
}





// This function updates the current sprite being display
void Animation::updateSprite() 
{

	// The following code determines if the current animation frame is the
	// last frame in the animation. If it is, cycle back to the start of the
	// vector other wise just go to the next frame.
	if (mCurrentIndex == mListOfSprites.size() - 1) 
	{
		mCurrentIndex = 0;
	}
	else 
	{
		mCurrentIndex++;
	}
}





// This function updates all of the sprite positions of the animation. 
// This is called from unit so the position update is based on where the unit is position
void Animation::updateSpritePositions( Vector2 newPos ) 
{
	for (int i = 0, max = mListOfSprites.size(); i < max; i++) 
	{
		mListOfSprites[i]->changeLoc( newPos.mX, newPos.mY );
	}
}





void Animation::cleanupAnimation() 
{
	mHasCleanedUp = true;
}