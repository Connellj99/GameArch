#include "Unit.h"
#include "Animations.h"

Unit::Unit(float xPos, float yPos, std::vector<Animations*> listOfAnims)
{
	mUnitLocationX = xPos;
	mUnitLocationY = yPos;
	mpAnimations = listOfAnims;
}

Unit::~Unit()
{
	mUnitOnScreen = false;
}


void Unit::updateUnitState(float timeAmt,bool speedUp, bool speedDown)
{
	//Goes through animation and puts in mpAnimations at i.
	//Enhanced For
	for (Animations* animation : mpAnimations)
	{

		animation->changeAnimationSpeed(speedUp, speedDown);
		animation->updateAnimation(timeAmt);

	}
}

void Unit::drawCurrentAnimation(System* systemObj,bool swap)
{
	mSwitchAnimations = swap;//take the passed in bool of can we swap
	setAnimation();//call the set animation function

	if (systemObj->getMoveSpriteStatus() == true)//if the sprite can move, aka the mouse was clicked
	{
		mUnitLocationX = systemObj->returnMousePos().getX();//systemObj->getMousePosX();//then set the unitlocation or spawn location to the mousePosition on x 
		mUnitLocationY = systemObj->returnMousePos().getY(); //systemObj->getMousePosY();//and on the y
	}
	
	systemObj->getGraphicSystem()->drawSprite(mpAnimations[mpCurrentAnimationIndex]->getCurrentSprite(), mUnitLocationX, mUnitLocationY);//draw the sprite with the correct animation and appropriate spawn locations
}

void Unit::setAnimation()
{
	if (mSwitchAnimations == true)//if we can animate
	{
		
		if (mpCurrentAnimationIndex >= mpAnimations.size() - 1)//if the current animation index reaches the max size -1(-1 because I start at 0 , then reset
		{
			mpCurrentAnimationIndex = 0;
		}
		else//else just add one to the index to go to next animation
			mpCurrentAnimationIndex++;
	}

}

void Unit::setUnitScreenStatus(bool unitOn)
{
	mUnitOnScreen = unitOn;
}
