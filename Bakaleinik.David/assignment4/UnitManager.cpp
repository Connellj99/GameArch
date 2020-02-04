#include "UnitManager.h"
#include"Unit.h"
#include "Animation.h"
#include "System.h"

int UnitManager::mCounter = 0;

UnitManager::UnitManager()
{
	
}

UnitManager::~UnitManager()
{
	clearAllUnits();
}

void UnitManager::addUnit(Unit* object)
{
	mpUnits.push_back(object);
}

void UnitManager::deleteUnit(int pointX, int pointY, int size) //iterate through map and ask each unit if it needs to be deleted through checkCollision()
{
	for (vector<Unit*>::iterator itr = mpUnits.begin(); itr != mpUnits.end(); itr++)
	{
		if ((*itr)->checkCollision(pointX, pointY, size))
		{
			delete *itr;
			mpUnits.erase(itr);
			return;
		}
	}
}

void UnitManager::clearAllUnits()
{
	for(vector<Unit*>::iterator itr = mpUnits.begin(); itr != mpUnits.end(); itr++)
	{ 
		delete *itr;
		
	}
	mpUnits.clear();
}

//Go through the map and call each unit's update()
void UnitManager::update(double frames)
{
	for (vector<Unit*>::iterator itr = mpUnits.begin(); itr != mpUnits.end(); itr++)
	{
		(*itr)->update(frames);
		
	}
}

//Go through the map and call every unit's draw()
void UnitManager::draw(System* systemObject)
{
	for (vector<Unit*>::iterator itr = mpUnits.begin(); itr != mpUnits.end(); itr++)
	{
		(*itr)->drawUnit(systemObject);
	}
}

void UnitManager::createNewUnit(Animation* startAnim, int posX, int posY)
{
	Unit* newUnit = new Unit(startAnim, posX, posY);
	
	mCounter++;
	

	addUnit(newUnit);
}

void UnitManager::disableAnimation()
{
	for (vector<Unit*>::iterator itr = mpUnits.begin(); itr != mpUnits.end(); itr++)
	{
		(*itr)->toggleAnimation();
	}
}

void UnitManager::switchHead(Animation* anim, Animation* otherAnim)
{
	
		if (mpUnits.size() >= 1)
		{

			if (getUnit(mpUnits.size() - 1)->getUnitAnimation().getAnimID() != anim->getAnimID())
			{
				getUnit(mpUnits.size()-1)->setUnitAnimation(anim);
				return;
			}
			else
			{
				getUnit(mpUnits.size()-1)->setUnitAnimation(otherAnim);
			}
		}
	
}
