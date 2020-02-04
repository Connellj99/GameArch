#include "UnitManager.h"
const int rangeX = 40;
const int rangeY = 40;

UnitManager::UnitManager() 
{
	
}

UnitManager::~UnitManager()
{
	cleanUp();
}

void UnitManager::updateAll(double looptime)
{
	for(unsigned int i = 0; i < mUnitHolder.size();i++)
	{
		mUnitHolder[i]->update(looptime);
	}
}

void UnitManager::drawAll()
{
	for (unsigned int i = 0; i < mUnitHolder.size(); i++)
	{
		mUnitHolder[i]->draw();
	}
}

void UnitManager::setAnimationAll()
{
	for (unsigned int i = 0; i < mUnitHolder.size(); i++)
	{
		mUnitHolder[i]->getCurrentAnimation()->switchLooping();
	}
}

void UnitManager::addUnit(float posX, float posY, float scale, std::vector<Sprites*> animationvector)
{
	Unit* currentUnit = new Unit(posX, posY, scale, animationvector);
	mUnitHolder.push_back(currentUnit);
	mpCurrentUnit = currentUnit;
}

bool UnitManager::isOverSprites(float clickedX, float clickedY)
{
	return false;
}

void UnitManager::cleanUp()
{
	for (unsigned int i = 0; i < mUnitHolder.size(); i++)
	{
		delete mUnitHolder[i];
	}
}

void UnitManager::removeUnit(float clickedX, float clickedY)
{
	for (unsigned int i = 0; i < mUnitHolder.size(); i++)
	{
		if (mUnitHolder[i]->getLocX() + rangeX > clickedX && mUnitHolder[i]->getLocX() - rangeX < clickedX)
		{
			if (mUnitHolder[i]->getLocY() + rangeY > clickedY && mUnitHolder[i]->getLocY() - rangeY < clickedY)
			{
				delete mUnitHolder[i];
				mUnitHolder.erase(mUnitHolder.begin() + i);
				std::cout << "deleted Unit";
			}
		}
	}
}