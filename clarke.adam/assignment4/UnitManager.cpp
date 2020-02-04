#include "UnitManager.h"

UnitManager::UnitManager()
{
}

UnitManager::~UnitManager()
{
}

Unit* UnitManager::createUnit(std::map<std::string, Animation>& animations, const Vector2D& initLoc,
	const Vector2D& scale)
{
	const auto unit = new Unit(animations, initLoc, scale);
	mUnits.push_back(unit);
	return unit;
}

std::vector<Unit*> UnitManager::getUnits(const Vector2D& atLoc)
{
	std::vector<Unit*> units;
	for (auto unit : mUnits)
	{
		if(unit->intersects(atLoc))
		{
			units.push_back(unit);
		}
	}
	return units;
}

bool UnitManager::destroyUnit(Unit* unit)
{
	auto mostRecentDestroyed = false;
	for (auto i = mUnits.begin(); i != mUnits.end(); ++i)
	{
		// free memory of unity and erase from vector if found
		if (*i == unit)
		{
			if (i == mUnits.end() - 1)
			{
				mostRecentDestroyed = true;
			}

			delete unit;
			mUnits.erase(i);

			break;
		}
	}
	return mostRecentDestroyed;
}

void UnitManager::toggleAnimations()
{
	for (auto unit : mUnits)
	{
		unit->toggleAnimation();
	}
}

void UnitManager::clear()
{
	for (auto unit : mUnits)
	{
		delete unit;
	}
	mUnits.clear();
}

void UnitManager::update()
{
	for (auto unit : mUnits)
	{
		unit->update();
	}
}

void UnitManager::draw()
{
	for (auto unit : mUnits)
	{
		unit->draw();
	}
}
