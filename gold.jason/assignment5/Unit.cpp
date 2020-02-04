#include"Unit.h"
#include"GraphicsSystem.h"
#include "Game.h"

Unit::Unit()
{

}

Unit::Unit(int xLoc, int yLoc, float scale, std::vector<Sprites*> animVector)
{
	mLocX = xLoc;
	mLocY = yLoc;
	mpCurrentAnimation = new Animations(animVector);
	mScale = scale;
	mCurrentAnimationsIndex = 0;
	mMaxAnimations = 0;
	mAnimationSets.push_back(mpCurrentAnimation);
}

Unit::~Unit()
{
	for(unsigned int i = 0; i < mAnimationSets.size(); i++)
	{
		delete mAnimationSets[i];
	}
}

void Unit::animationCleanUp()
{
	for (unsigned int i = 0; i < mAnimationSets.size(); i++)
	{
		delete mAnimationSets[i];
	}
}


void Unit::update(double time)
{
	mpCurrentAnimation->Update(time);
}

void Unit::draw()
{
	Game::getInstance()->getSystem()->getGraphicsSystem()->draw(mLocX, mLocY, /*mAnimationSets[currentanim]->getCurrentSprite()*/mpCurrentAnimation->getCurrentSprite(), mScale);
}

void Unit::setAnimation()
{
	mCurrentAnimationsIndex++;
	if(mCurrentAnimationsIndex > mMaxAnimations)
	{
		mCurrentAnimationsIndex = 0;
		std::cout << "Anim1" << std::endl;
	}
	mpCurrentAnimation = mAnimationSets[mCurrentAnimationsIndex];
	std::cout << "Anim2" << std::endl;
}

void Unit::addAnimations(std::vector<Sprites*> animVector)
{
	Animations* temp = new Animations(animVector);
	mAnimationSets.push_back(temp);
	mMaxAnimations++;
}

void Unit::setLocX(int x)
{
	mLocX = x;
}

void Unit::setLocY(int y)
{
	mLocY = y;
}