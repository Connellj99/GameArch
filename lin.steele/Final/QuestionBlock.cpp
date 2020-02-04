#include "QuestionBlock.h"



// This function is the default constructor for the class 
QuestionBlock::QuestionBlock() : Unit()
{
	mUnitType = QUESTION_BLOCK;
	mIsEmpty = false;
}





// This is the destructor for the class
QuestionBlock::~QuestionBlock()
{

}





// This constructor moves the player Unit to a given position
QuestionBlock::QuestionBlock(Vector2 newPos)
{
	mCurrentLocation = newPos;
	mUnitType = QUESTION_BLOCK;
	mIsEmpty = false;
}





// This function is the update function for the Question Block Unit
void QuestionBlock::update(double newTimeBetweenFrames)
{
	if (isAnimationStopped == false)
	{
		// The following code updates the current frame of the animation
		mCurrentAnimations[mCurrentAnimationIndex]->update(newTimeBetweenFrames);
	}
}





// This function swaps the animations of the unit
void QuestionBlock::swapAnimation( string nameOfNewAnimation )
{
	if (mIsEmpty == false) 
	{
		// The following code determines if the current animation is the
		// last animation in the animations vector. If it is, cycle back to 
		// the start of the vector other wise just go to the next animation.
		for (int i = 0, max = mCurrentAnimations.size(); i < max; i++)
		{
			if (mCurrentAnimations[i]->getAnimationName() == nameOfNewAnimation)
			{
				mCurrentAnimationIndex = i;
			}
		}
		mIsEmpty = true;
	}
}