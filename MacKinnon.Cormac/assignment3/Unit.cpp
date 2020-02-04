#include "Unit.h"


//constuctor
Unit::Unit()
{
	mUnitLocation = Vector2D(0, 0);
	mCurrentIndexPos = 0;
}

Unit::Unit(Vector2D unitLocation)
{
	mUnitLocation = unitLocation;
}

//destructor
Unit::~Unit()
{
}
//updates the current animation through the update function in the animation class
void Unit::update()
{
	mpAnimationsList[mCurrentIndexPos]->update();
}
//draws the current sprite in the animation to the location specified
void Unit::draw()
{
	gpGame->getSystem()->getGraphicsSystem()->draw( mUnitLocation.getX(), mUnitLocation.getY(), mpAnimationsList[mCurrentIndexPos]->getCurrentSprite(), SCALE_FACTOR_DEFAULT);
}
//switches between the dean and smurf animations
void Unit::setAnimation()
{
	if (mCurrentIndexPos == mpAnimationsList.size() - 1) 
	{
		mCurrentIndexPos = 0;
	}
	else 
	{
		mCurrentIndexPos += 1;
	}
}
//adds animations to a vector
void Unit::addAnimation(Animation * animation)
{
	mpAnimationsList.push_back(animation);
}
//sets the location of the unit
void Unit::setUnitLocation(Vector2D unitLocation)
{
	mUnitLocation = unitLocation;
}
//checks to see if the unit is visible
bool Unit::isVisible()
{
	return mUnitLocation.getX() > 0 && mUnitLocation.getX() < DISP_WIDTH && mUnitLocation.getY() > 0 && mUnitLocation.getY() < DISP_HEIGHT;
}
//gets the current animation
Animation* Unit::getCurrentAnimation()
{
	return mpAnimationsList[mCurrentIndexPos];
}
