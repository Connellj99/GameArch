#include "UnitManager.h"
#include "EventSystem.h"
#include "Game.h"
#include "CreateUnitEvent.h"
#include "DeleteUnitEvent.h"


//constructor
UnitManager::UnitManager()
{
}

//destructor
UnitManager::~UnitManager()
{
	cleanup();
}

void UnitManager::cleanup()
{
	clear();
}

//updates each unit
void UnitManager::update(double time)
{
	for (unsigned int i = 0; i < mpUnitContainer.size(); i++) 
	{
		mpUnitContainer[i]->update(time);
	}
}

//draws all the units that have bene made
void UnitManager::draw()
{
	for (unsigned int i = 0; i < mpUnitContainer.size(); i++) 
	{
		mpUnitContainer[i]->draw();
	}
}

//adds new unit and makes it the current unit
void UnitManager::addUnit(Vector2D location, std::vector<Sprite*> animationList)
{
	Unit* pCurrentUnit = new Unit(location - SMURF_HEIGHT * 0.5f, animationList);
	mpUnitContainer.push_back(pCurrentUnit);
	mpCurrentUnit = pCurrentUnit;
}

//gets the current unit
Unit* UnitManager::getUnit()
{
	return mpCurrentUnit;
}

//deletes all remaining units during cleanup
void UnitManager::clear()
{
	for (unsigned int i = 0; i < mpUnitContainer.size(); i++) 
	{
		delete mpUnitContainer[i];
	}
	mpUnitContainer.clear();
}

//deletes the units within the specified area
void UnitManager::removeUnits(Vector2D location)
{
	for (unsigned int i = 0; i < mpUnitContainer.size(); i++) 
	{
		if (mpUnitContainer[i]->getUnitLocX() + X_BOUND > location.getX() && mpUnitContainer[i]->getUnitLocX() - X_BOUND < location.getX()) 
		{
			if (mpUnitContainer[i]->getUnitLocY() + Y_BOUND > location.getY() && mpUnitContainer[i]->getUnitLocY() - Y_BOUND < location.getY()) 
			{
				delete mpUnitContainer[i];
				mpUnitContainer.erase(mpUnitContainer.begin() + i);
			}
		}
	}
}

//toggles wheter or not the animation is active for the units on screen
void UnitManager::toggleAnimationActive()
{
	for (unsigned int i = 0; i < mpUnitContainer.size(); i++) 
	{
		mpUnitContainer[i]->getCurrentAnimation()->animationState();
	}
}
