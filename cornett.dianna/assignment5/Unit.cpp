/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#include "Unit.h"

/*
Set up a unit at the given position containing no animations
*/
Unit::Unit(Position pos, int width, int height)
{
	mX = pos.x;
	mY = pos.y;
	mWidth = width;
	mHeight = height;
}

/*
Constructor that takes vector of animations and position
*/
Unit::Unit(std::vector<Animation *> animations, Position pos, int width, int height)
{
	mX = pos.x;
	mY = pos.y;
	mWidth = width;
	mHeight = height;
	mAnimations = animations;
}


/*
Destroy the Unit and dellocate all memory
*/
Unit::~Unit()
{
	for (Animation * animation : mAnimations)
	{
		delete animation;
	}
}

/*
Update the state of the unit
*/
void Unit::update(double deltaTime)
{
	if (mIsAnimating) 
	{
		mAnimations[mCurrentAnimation]->update(deltaTime);
	}
}

/*
Draw the current animation centered on its positon
*/
void Unit::draw(System * system)
{
	system->getGraphicsSystem()->draw(getCurrentAnimation()->getCurrentSprite(), getCenteredPosition().x, getCenteredPosition().y);
}


/*
Add a new animation to the Unit
*/
void Unit::addAnimation(Animation * animation)
{
	mAnimations.push_back(animation);
}

/*
Change the animation speed by amount
*/
void Unit::changeAnimationSpeed(double amount)
{
	for (Animation * animation : mAnimations)
	{
		animation->changeAnimationSpeed(amount);
	}
}

/*
Check if a given position is inside the unit
*/
bool Unit::positionIsInUnit(Position pos)
{
	return (((mX < pos.x) && (pos.x < (mX + mWidth))) && ((mY < pos.y) && (pos.y < (mY + mHeight))));
}

//GETTERS
/*
Get the current animation
*/
Animation * Unit::getCurrentAnimation()
{
	return mAnimations[mCurrentAnimation];
}

Position Unit::getCenteredPosition()
{
	return Position(mX - mWidth / 2, mY - mHeight / 2);
}

//SETTERS
/*
Go to next animation
*/
void Unit::setAnimation()
{
	if (mCurrentAnimation < mAnimations.size() - 1) //Only update the counter if it is less then the length of the list (doing so must not cause it to overrun bounds)
	{
		mCurrentAnimation++;
	}
	else
	{ //If you are on the last sprite
		mCurrentAnimation = 0; //Send the user back to the first sprite
	}
}

/*
Set the position
*/
void Unit::setPosition(Position pos)
{
	mX = pos.x;
	mY = pos.y;
}

/*
Check if the unit should animate
*/
void Unit::setIsAnimating(bool isAnimating) 
{
	mIsAnimating = isAnimating;
}