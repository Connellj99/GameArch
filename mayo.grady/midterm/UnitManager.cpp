/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 4
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "UnitManager.h"

UnitManager::UnitManager()
{

}

UnitManager::~UnitManager()
{
	cleanup();
}

void UnitManager::add(Vector2D position)
{
	mvCollection.push_back(new Unit(position.getX(), position.getY()));
}

void UnitManager::remove(Vector2D position)
{
	int size = mvCollection.size();
	for (int i = 0; i < size - 1; i++)
	{
		//find the bounds of the current unit
		int rightBound = mvCollection[i]->getLocation().getX() + RADIUS;
		int leftBound = mvCollection[i]->getLocation().getX() - RADIUS;
		int upperBound = mvCollection[i]->getLocation().getY() + RADIUS;
		int lowerBound = mvCollection[i]->getLocation().getY() - RADIUS;

		//if the passed in position is within those bounds, delete the pointer and erase the vector entry
		if (position.getX() < rightBound && position.getX() > leftBound)
		{
			if (position.getY() < upperBound && position.getY() > lowerBound)
			{
				delete mvCollection[i];
				mvCollection.erase(mvCollection.begin() + i);
				size--;
			}
		}
	}
}

void UnitManager::remove(int index)
{
	delete mvCollection[index];
	mvCollection.erase(mvCollection.begin() + index);
}

Unit * UnitManager::getUnit(int index)
{
	return mvCollection[index];
}

void UnitManager::cleanup()
{
	int size = mvCollection.size();
	for (int i = 0; i < size; i++)
	{
		delete mvCollection[i];
	}
	mvCollection.clear();
}

void UnitManager::update(double dT)
{
	int size = mvCollection.size();
	for (int i = 0; i < size; i++)
	{
		mvCollection[i]->update(dT);
	}
}

void UnitManager::draw()
{
	int size = mvCollection.size();
	for (int i = 0; i < size; i++)
	{
		mvCollection[i]->draw();
	}
}

int UnitManager::getCollectionSize()
{
	return mvCollection.size();
}

void UnitManager::toggleAnim()
{
	int size = mvCollection.size();
	for (int i = 0; i < size; i++)
	{
		mvCollection[i]->getAnimation()->toggleAnim();
	}
}