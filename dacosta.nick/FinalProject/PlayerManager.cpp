#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <cassert>

#include "Trackable.h"

#include "BufferFlags.h"
#include "FontFlags.h"
#include "DirectionKeys.h"
#include "UnitTypes.h"

#include "EventTypes.h"

#include "Event.h"
#include "EventListener.h"

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
#include "EventSystem.h"
#include "UnitManager.h"
#include "PlayerManager.h"


PlayerManager::PlayerManager()
{

}

PlayerManager::~PlayerManager()
{
	// Clean up the manager.
	cleanUp();

	return;
}

void PlayerManager::cleanUp()
{
	clear();

	return;
}

void PlayerManager::addUnit(Player* _pPlayer)
{
	// Add a new unit to the list.
	mvPlayer.push_back(_pPlayer);

	return;
}

void PlayerManager::deleteUnit(int _collisionX, int _collisionY)
{
	// Adjustment to check from beginning of the list to this position.
	int counter = mvPlayer.size();

	if (!mvPlayer.empty())
	{
		// Search the list for the last instance with a collision at the collision position.
		for (std::vector<Player*>::reverse_iterator currentUnit = mvPlayer.rbegin(); currentUnit != mvPlayer.rend(); ++currentUnit)
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
				mvPlayer.erase(mvPlayer.begin() + counter);

				// Collision taken care of so exit.
				return;
			}
		}
	}

	return;
}

Player* PlayerManager::getUnit()
{
	if (!mvPlayer.empty())
	{
		return mvPlayer.back();
	}

	return nullptr;
}

Player* PlayerManager::getUnit(int _position)
{
	if (!mvPlayer.empty())
	{
		return mvPlayer.at(_position);
	}

	return nullptr;
}

void PlayerManager::draw(GraphicsSystem* _pGraphicsSystem)
{
	if (!mvPlayer.empty())
	{
		for each (Player* pPlayer in mvPlayer)
		{
			pPlayer->draw(_pGraphicsSystem);
		}
	}

	return;
}

void PlayerManager::setDirection(int _direction)
{
	if (!mvPlayer.empty())
	{
		Player* pHeadUnit = mvPlayer[0];

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

void PlayerManager::update(double _deltaTime)
{
	if (!mvPlayer.empty())
	{
		Player* pHeadUnit = mvPlayer[0];

		double distanceBefore = std::sqrt(std::pow(pHeadUnit->getDestinationX() - pHeadUnit->getPositionX(), 2) + std::pow(pHeadUnit->getDestinationY() - pHeadUnit->getPositionY(), 2));

		// Move all the segments of the unit.
		for (size_t counter = 0; counter < mvPlayer.size(); counter++)
		{
			// Get the current unit.
			Player* pCurrentUnit = mvPlayer[counter];

			// Update the unit's animation.
			pCurrentUnit->update(_deltaTime);

			//pCurrentUnit->move(_deltaTime);
		}

		// Check if the head reached its destination. (All segments did as well)
		double distanceAfter = std::sqrt(std::pow(pHeadUnit->getDestinationX() - pHeadUnit->getPositionX(), 2) + std::pow(pHeadUnit->getDestinationY() - pHeadUnit->getPositionY(), 2));

		// Reached destination update path.
		if (distanceAfter >= distanceBefore)
		{
			pHeadUnit->setPosition(pHeadUnit->getDestinationX(), pHeadUnit->getDestinationY());
			// Start from the tail and work to the head. Update all the directions and destinations.
			for (int counter = mvPlayer.size() - 1; counter >= 0; counter--)
			{
				Player* pCurrentUnit = mvPlayer[counter];

				// Head has no previous segment.
				if (counter > 0)
				{
					Player* pPreviousUnit = mvPlayer[counter - 1];

					pCurrentUnit->setQueueDirection(pPreviousUnit->getDirection());
				}

				pCurrentUnit->setDirection(pCurrentUnit->getQueueDirection());

				//pCurrentUnit->updateHead();
			}
		}
	}

	return;
}

void PlayerManager::clear()
{
	if (!mvPlayer.empty())
	{
		// Loop through the list and delete each unit pointer.
		for each (Player* pPlayer in mvPlayer)
		{
			// Clean the unit.
			pPlayer->cleanUp();

			// Delete the current unit in the list.
			delete pPlayer;

			// Set the current unit to null.
			pPlayer = nullptr;
		}
	}

	// Empty the vector.
	mvPlayer.clear();

	return;
}
