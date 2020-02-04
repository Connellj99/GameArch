/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <vector>
#include <iostream>
#include <map>

#include "Trackable.h"

#include "BufferFlags.h"
#include "FontFlags.h"

#include "Color.h"
#include "Font.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Animation.h"
#include "GraphicsSystem.h"
#include "Unit.h"
#include "UnitManager.h"

// Constructor.
UnitManager::UnitManager()
{
	return;
}

// Destructor.
UnitManager::~UnitManager()
{
	// Clean up the manager.
	cleanUp();

	return;
}

// Clean up the manager.
void UnitManager::cleanUp()
{
	clear();

	return;
}

// Add a new unit to the list.
void UnitManager::addUnit(Unit* _pUnit)
{
	// Add a new unit to the list.
	mvUnits.push_back(_pUnit);

	return;
}

// Remove a unit based on collision coordinates.
void UnitManager::deleteUnit(int _collisionX, int _collisionY)
{
	// Adjustment to check from beginning of the list to this position.
	int counter = mvUnits.size();

	if (!mvUnits.empty())
	{
		// Search the list for the last instance with a collision at the collision position.
		for (std::vector<Unit*>::reverse_iterator currentUnit = mvUnits.rbegin(); currentUnit != mvUnits.rend(); ++currentUnit)
		{
			// Reduce the poisition.
			counter--;

			if ((*currentUnit)->collision(_collisionX, _collisionY))
			{
				// Delete the pointer.
				delete (*currentUnit);

				// Reset the memory allocation.
				(*currentUnit) = nullptr;

				// Erase the unit from the vector.
				mvUnits.erase(mvUnits.begin() + counter);

				// Collision taken care of so exit.
				return;
			}
		}
	}

	return;
}

// Get the last unit.
Unit* UnitManager::getUnit()
{
	if (!mvUnits.empty())
	{
		return mvUnits.back();
	}

	return nullptr;
}

// Draw each unit to the screen.
void UnitManager::draw(GraphicsSystem* _pGraphicsSystem)
{
	if (!mvUnits.empty())
	{
		for each (Unit* pUnit in mvUnits)
		{
			pUnit->draw(_pGraphicsSystem);
		}
	}

	return;
}

// Toggle the animate setting for each unit on/off.
void UnitManager::toggleAnimation()
{
	if (!mvUnits.empty())
	{
		for each (Unit* pUnit in mvUnits)
		{
			pUnit->toggleAnimate();
		}
	}

	return;
}

// Update each unit's animation.
void UnitManager::update(double _deltaTime)
{
	if (!mvUnits.empty())
	{
		for each (Unit* pUnit in mvUnits)
		{
			pUnit->update(_deltaTime);
		}
	}

	return;
}

// Clear all the units.
void UnitManager::clear()
{
	if (!mvUnits.empty())
	{
		// Loop through the list and delete each unit pointer.
		for each (Unit* pUnit in mvUnits)
		{
			// Clean the unit.
			pUnit->cleanUp();

			// Delete the current unit in the list.
			delete pUnit;

			// Set the current unit to null.
			pUnit = nullptr;
		}
	}

	// Empty the vector.
	mvUnits.clear();

	return;
}
