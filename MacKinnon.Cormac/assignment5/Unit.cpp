#include "Unit.h"
#include "Game.h"


//constuctor
Unit::Unit()
{
	mUnitLocation = Vector2D(0, 0);
	mCurrentIndexPos = 0;
}

Unit::Unit(Vector2D unitLocation, std::vector<Sprite*> animationList)
{
	mUnitLocation = unitLocation;
	mpCurrentAnim = new Animation(animationList);
	mCurrentIndexPos = 0;
	addAnimation(mpCurrentAnim);
	mpTimer = new Timer();
	mpTimer->start();
}

//destructor
Unit::~Unit()
{
	for (unsigned int i = 0; i < mpAnimationsList.size(); i++) 
	{
		delete mpAnimationsList[i];
	}

	delete mpTimer;
}
//updates the current animation through the update function in the animation class
void Unit::update(double time)
{
	mpAnimationsList[mCurrentIndexPos]->update(time);
}
//draws the current sprite in the animation to the location specified
void Unit::draw()
{
	Game::getInstance()->getSystem()->getGraphicsSystem()->draw( mUnitLocation.getX(), mUnitLocation.getY(), mpAnimationsList[mCurrentIndexPos]->getCurrentSprite(), SCALE_FACTOR_DEFAULT);
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

void Unit::addAnimation(std::vector<Sprite*> animationList)
{
	Animation* pAnimation = new Animation(animationList);
	mpAnimationsList.push_back(pAnimation);

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
Vector2D Unit::getLocation()
{
	return mUnitLocation;
}
int Unit::getUnitLocX()
{
	return mUnitLocation.getX();
}
int Unit::getUnitLocY()
{
	return mUnitLocation.getY();
}
//gets the current animation
Animation* Unit::getCurrentAnimation()
{
	return mpAnimationsList[mCurrentIndexPos];
}
