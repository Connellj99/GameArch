#include "UnitManager.h"

UnitManager::UnitManager()
{
	mpUnitVec.clear();
}

UnitManager::~UnitManager()
{
	if (mpUnitVec.empty())
		return;
	int max = mpUnitVec.size();

	for (int i = 0; i<max; i++)
	{
		delete mpUnitVec[i];
		mpUnitVec[i] = nullptr;
	}
	mpUnitVec.clear();
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

void UnitManager::createUnit(Animation ani, Vector2D position)
{
	Unit* temp = new Unit(ani, position);
	mpUnitVec.push_back(temp);
}

void UnitManager::createUnit(vector<Animation> ani, Vector2D position)
{
	Unit* temp = new Unit(ani, position);
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

void UnitManager::deleteAllUnits()
{
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
		Vector2D aniLoc = Vector2D(mpUnitVec[i]->getPosition().getX(),
			mpUnitVec[i]->getPosition().getY());

		if (aniLoc.getX() + 35 > pos.getX() && aniLoc.getX() - 35 < pos.getX()
			&& aniLoc.getY() + 35 > pos.getY() && aniLoc.getY() - 35 < pos.getY())
		{
			delete mpUnitVec[i];
			mpUnitVec[i] = nullptr;
			mpUnitVec.erase(mpUnitVec.begin() + i);
		}
	}
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
