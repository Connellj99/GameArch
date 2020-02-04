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
#include <string>
#include <cassert>

#include "Trackable.h"

#include "BufferFlags.h"
#include "FontFlags.h"
#include "KeyCodes.h"
#include "DirectionKeys.h"
#include "UnitTypes.h"

#include "EventTypes.h"

#include "Event.h"

#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "UnitEvents.h"
#include "GameEvents.h"

#include "Color.h"
#include "Font.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Animation.h"
#include "GraphicsSystem.h"
#include "Level.h"
#include "LevelManager.h"
#include "Unit.h"
#include "Player.h"
#include "EventListener.h"
#include "EventSystem.h"
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

// Get the last unit.
Unit* UnitManager::getUnit()
{
	if (!mvUnits.empty())
	{
		return mvUnits.back();
	}

	return nullptr;
}

// Get the unit at the position.
Unit* UnitManager::getUnit(int _position)
{
	if (!mvUnits.empty())
	{
		return mvUnits.at(_position);
	}

	return nullptr;
}

Player * UnitManager::getPlayer()
{
	for (std::vector<Unit*>::reverse_iterator currentUnit = mvUnits.rbegin(); currentUnit != mvUnits.rend(); ++currentUnit)
	{
		int type = (*currentUnit)->getType();

		if (type == PLAYER)
		{
			return (Player*)(*currentUnit);
		}
	}

	return nullptr;
}

Player* UnitManager::getPlayer(int _position)
{
	// Counter for current player unit.
	int counter = 0;

	for (std::vector<Unit*>::iterator currentUnit = mvUnits.begin(); currentUnit != mvUnits.end(); ++currentUnit)
	{
		int type = (*currentUnit)->getType();

		if (type == PLAYER)
		{
			if (counter == _position)
			{
				return (Player*)(*currentUnit);
			}
			
			// Player found, but not at correct position.
			counter++;
		}

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
void UnitManager::update(double _deltaTime, LevelManager* _pLevelManager)
{
	if (!mvUnits.empty())
	{
		// Move all the segments of the unit.
		for (size_t counter = 0; counter < mvUnits.size(); counter++)
		{
			// Get the current unit.
			Unit* pCurrentUnit = mvUnits[counter];

			// Update the unit's animation.
			pCurrentUnit->update(_deltaTime);
		}

		Player* pHeadUnit = getPlayer(0);

		if (pHeadUnit != nullptr)
		{
			double distanceBefore = std::sqrt(std::pow(pHeadUnit->getDestinationX() - pHeadUnit->getPositionX(), 2) + std::pow(pHeadUnit->getDestinationY() - pHeadUnit->getPositionY(), 2));

			// Move all the segments of the unit.
			for each (Unit* pUnit in mvUnits)
			{
				// Get the current unit.
				if (pUnit->getType() == PLAYER)
				{
					((Player*)pUnit)->move(_deltaTime, _pLevelManager);
				}
			}

			checkForCollisions();

			// Check if the head reached its destination. (All segments did as well)
			double distanceAfter = std::sqrt(std::pow(pHeadUnit->getDestinationX() - pHeadUnit->getPositionX(), 2) + std::pow(pHeadUnit->getDestinationY() - pHeadUnit->getPositionY(), 2));

			// Reached destination update path.
			if (distanceAfter >= distanceBefore)
			{
				pHeadUnit->setPosition(pHeadUnit->getDestinationX(), pHeadUnit->getDestinationY());

				Player* pCurrentUnit = nullptr;
				Player* pPreviousUnit = nullptr;

				// Start from the tail and work to the head. Update all the directions and destinations.
				for (int counter = (mvUnits.size() - 1); counter >= 0; counter--)
				{
					if (mvUnits[counter]->getType() == PLAYER)
					{
						pCurrentUnit = (Player*)mvUnits[counter];

						if (pPreviousUnit != nullptr)
						{
							pPreviousUnit->setQueueDirection(pCurrentUnit->getDirection());
							pPreviousUnit->updateDirection();
							pPreviousUnit->updateDestination();
						}

						pPreviousUnit = pCurrentUnit;
					}
				}

				pHeadUnit->updateDirection();
				pHeadUnit->updateDestination();
			}
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

	mPlayerSize = 0;

	return;
}

// TODO
void UnitManager::setDirection(int _direction)
{
	if (!mvUnits.empty())
	{
		Player* pHeadUnit = getPlayer(0);

		if ((pHeadUnit->getDirection() + 2) % 4 != _direction)
		{
			pHeadUnit->setQueueDirection(_direction);

			int distance = pHeadUnit->getDistance();

			int destinationX = pHeadUnit->getDestinationX();
			int destinationY = pHeadUnit->getDestinationY();

			switch (_direction)
			{

			case SOUTH:
				pHeadUnit->setQueueDestination(destinationX, destinationY + distance);
				break;
			case WEST:
				pHeadUnit->setQueueDestination(destinationX - distance, destinationY);
				break;
			case NORTH:
				pHeadUnit->setQueueDestination(destinationX, destinationY - distance);
				break;
			case EAST:
				pHeadUnit->setQueueDestination(destinationX + distance, destinationY);
				break;
			default:
				break;
			}
		}
	}

	return;
}

void UnitManager::updatePlayerSize()
{
	mPlayerSize++;

	return;
}

int UnitManager::getPlayerSize()
{
	return mPlayerSize;
}

void UnitManager::checkForCollisions()
{
	// Check if the head is colliding with anything but the second player unit.
	Player* pHeadUnit = getPlayer(0);
	Player* pSecondUnit = getPlayer(1);

	for each (Unit* pUnit in mvUnits)
	{
		if (pUnit == pHeadUnit || pUnit == pSecondUnit)
		{
			continue;
		}

		if (pHeadUnit->getPositionX() < pUnit->getPositionX() + pUnit->getWidth() &&
			pHeadUnit->getPositionX() + pHeadUnit->getWidth() > pUnit->getPositionX() &&
			pHeadUnit->getPositionY() < pUnit->getPositionY() + pUnit->getHeight() &&
			pHeadUnit->getPositionY() + pHeadUnit->getHeight() > pUnit->getPositionY())
		{
			EventSystem::getInstance()->performEvent(CollisionUnitEvent(pUnit->getType()));

			switch (pUnit->getType())
			{
				case FOOD:
					removeFood();
					break;
				case SPEED_UP_COLLECTABLE:
				case SLOW_DOWN_COLLECTABLE:
				case POINTS_COLLECTABLE:
					removeCollectable(pUnit->getPositionX(), pUnit->getPositionY());
					break;
				default:
					break;
			}

			return;
		}
	}

	return;
}

void UnitManager::removeFood()
{
	if (!mvUnits.empty())
	{
		for (int counter = 0; counter < mvUnits.size(); counter++)
		{
			if (mvUnits[counter]->getType() == FOOD)
			{
				delete mvUnits[counter];

				mvUnits[counter] = nullptr;

				mvUnits.erase(mvUnits.begin() + counter);

				return;
			}
		}
	}

	return;
}

void UnitManager::removeCollectable(int _positionX, int _positionY)
{
	if (!mvUnits.empty())
	{
		for (int counter = 0; counter < mvUnits.size(); counter++)
		{
			Unit* pUnit = mvUnits[counter];

			switch (pUnit->getType())
			{
				case SLOW_DOWN_COLLECTABLE:
				case SPEED_UP_COLLECTABLE:
				case POINTS_COLLECTABLE:
					if (pUnit->getPositionX() == _positionX && pUnit->getPositionY() == _positionY)
					{
						delete pUnit;

						pUnit = nullptr;

						mvUnits.erase(mvUnits.begin() + counter);

						return;
					}
					break;
				default:
					break;
			}
		}
	}

	return;
}

