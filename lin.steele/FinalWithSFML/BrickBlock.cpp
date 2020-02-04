#include "BrickBlock.h"



// This function is the default constructor for the class 
BrickBlock::BrickBlock() : Unit()
{
	mUnitType = BRICK_BLOCK;
}





// This is the destructor for the class
BrickBlock::~BrickBlock()
{

}





// This constructor moves the player Unit to a given position
BrickBlock::BrickBlock(Vector2 newPos)
{
	mCurrentLocation = newPos;
	mUnitType = BRICK_BLOCK;
}





// This function is the update function for the Question Block Unit
void BrickBlock::update(double newTimeBetweenFrames)
{
	if (isAnimationStopped == false)
	{
		// The following code updates the current frame of the animation
		mCurrentAnimations[mCurrentAnimationIndex]->update(newTimeBetweenFrames);
	}
}