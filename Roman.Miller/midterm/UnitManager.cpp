#include "UnitManager.h"
#include "EventSystem.h"
#include "GameEvent.h"

UnitManager::UnitManager()
{
	mpUnitVec.clear();
}

UnitManager::~UnitManager()
{
	deleteAllUnits();
}

void UnitManager::addUnit(Unit* unit)
{
	mpUnitVec.push_back(unit);
}

void UnitManager::addUnit(vector<Unit*> unit)
{
	for (int i = 0; i < unit.size(); i++)
	{
		mpUnitVec.push_back(unit[i]);
	}

}

void UnitManager::createUnit(Animation ani, Vector2D position, string type)
{
	Unit* temp = new Unit(ani, position, type);
	mpUnitVec.push_back(temp);
}

void UnitManager::createUnit(vector<Animation> ani, Vector2D position, string type)
{
	Unit* temp = new Unit(ani, position, type);
	mpUnitVec.push_back(temp);
	temp = nullptr;
}


void UnitManager::updateUnit()
{
	for (int i = 0; i < mpUnitVec.size(); i++)
	{
		mpUnitVec[i]->update();
	}
}

void UnitManager::updateUnit(int index)
{
	mpUnitVec[index]->update();
}

Unit * UnitManager::getUnit(int index)
{
	return mpUnitVec[index];
}

Unit * UnitManager::getUnit()
{
	if (mpUnitVec.empty())
		return nullptr;

	return mpUnitVec.back();
}

void UnitManager::checkOverlap(Vector2D pos)
{
	for (unsigned int i = 0; i < mpUnitVec.size(); i++)
	{

		if (pos == mpUnitVec[i]->getPosition())
		{
			if (mpUnitVec[i]->getType() == "food")
			{
				EventSystem::getInstance()->fireEvent(Event((EventType)EAT));
			}
			else if (mpUnitVec[i]->getType() == "slow")
			{
				EventSystem::getInstance()->fireEvent(Event((EventType)SLOW));
			}
			else if (mpUnitVec[i]->getType() == "speed")
			{
				EventSystem::getInstance()->fireEvent(Event((EventType)SPEED));
			}
			deleteByIndex(i);
			return;
		}
	}
}

void UnitManager::deleteAllUnits()
{
	if (mpUnitVec.empty())
		return;

	for (int i = 0; i < mpUnitVec.size(); i++)
	{
		delete mpUnitVec[i];
		mpUnitVec[i] = nullptr;
	}
	mpUnitVec.clear();
}

void UnitManager::deleteByPosition(Vector2D pos)
{
	for (unsigned int i = 0; i < mpUnitVec.size(); i++)
	{

		if (pos == mpUnitVec[i]->getPosition())
		{
			deleteByIndex(i);
		}
	}
}

void UnitManager::deleteByPositionAndType(Vector2D pos, string type)
{
	for (unsigned int i = 0; i < mpUnitVec.size(); i++)
	{

		if (pos == mpUnitVec[i]->getPosition() && type == mpUnitVec[i]->getType())
		{
			deleteByIndex(i);
		}
	}
}

void UnitManager::deleteByIndex(int i)
{
	delete mpUnitVec[i];
	mpUnitVec[i] = nullptr;
	mpUnitVec.erase(mpUnitVec.begin() + i);
}

bool UnitManager::containsObjectOfType(string type)
{
	for (int i = 0; i < mpUnitVec.size(); i++)
	{
		if (type == mpUnitVec[i]->getType())
		{
			return true;
		}
	}
	return false;
}

void UnitManager::draw(int index)
{
	mpUnitVec[index]->draw();
}

void UnitManager::draw()
{
	for (int i = 0; i < mpUnitVec.size(); i++)
	{
		mpUnitVec[i]->draw();
	}
}

void UnitManager::pausePlayAllUnits()
{
	for (int i = 0; i < mpUnitVec.size(); i++)
	{
		mpUnitVec[i]->pausePlayAnimation();
	}
}
