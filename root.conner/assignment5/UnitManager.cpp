/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include <PerformanceTracker.h>

#include "UnitManager.h"

// Constructor
UnitManager::UnitManager()
{
}
UnitManager::UnitManager(Animation* a, Animation* b)
{
	mpAnim1 = a;
	mpAnim2 = b;
}

// Add animation
void UnitManager::addAnim(GraphicsBuffer* gB, int wdth, int hght, float sp, bool loop)
{
	// Add up to two animations
	if (mpAnim1 == nullptr)
		mpAnim1 = new Animation(gB, wdth, hght, sp, loop);
	else if (mpAnim2 == nullptr)
		mpAnim2 = new Animation(gB, wdth, hght, sp, loop);
}

// Add units
void UnitManager::addUnit(int xPos,int yPos)
{
	Unit* pTempCharacter = new Unit(xPos, yPos, mpAnim1);
	pTempCharacter->setLocation(xPos, yPos);
	mpCharacterList.push_back(pTempCharacter);
}

// Accessor
Unit* UnitManager::getUnit()
{
	return mpCharacterList[mpCharacterList.size()-1];
}

// Other functions
void UnitManager::switchAnimation()
{
	if (mAnimDean)
	{
		mpCharacterList[mpCharacterList.size()-1]->setAnimation(mpAnim2);
		mAnimDean = false;
	}
	else 
	{
		mpCharacterList[mpCharacterList.size()-1]->setAnimation(mpAnim1);
		mAnimDean = true;
	}
}

void UnitManager::toggleAnimationPause()
{
	mpAnim1->togglePause();
	mpAnim2->togglePause();
}

void UnitManager::updateUnits()
{
	for each (Unit* u in mpCharacterList)
	{
		u->update();
	}
}

void UnitManager::drawUnits()
{
	for each (Unit* u in mpCharacterList)
	{
		u->draw();
	}
}

// Delete units
void UnitManager::deleteUnit(int x, int y)
{
	for (int i = 0; i < (int)mpCharacterList.size(); i++)
	{
		if (abs(mpCharacterList[i]->getXPos() - x + 30) < 30 && abs(mpCharacterList[i]->getYPos() - y + 30) < 30)
		{
			delete mpCharacterList[i];
			mpCharacterList.erase(mpCharacterList.begin() + i);
		}
	}
}

void UnitManager::deleteAllUnits()
{
	int size = (int)mpCharacterList.size();
	for (int i = 0; i < size; i++)
	{
		delete mpCharacterList[0];
		mpCharacterList.erase(mpCharacterList.begin());
	}
}

UnitManager::~UnitManager() 
{ 
	delete mpAnim1;
	delete mpAnim2;

	deleteAllUnits(); 
}