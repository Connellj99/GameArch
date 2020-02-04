#include "UnitManager.h"

UnitManager::UnitManager()
{
	initUnitManager();
}

UnitManager::~UnitManager()
{
	cleanup();
	unitManager.empty();
	unitManager.clear();
}

void UnitManager::cleanup()
{
	if(!unitManager.empty())
	{
		for (unsigned int i = 0; i < unitManager.size(); i++) {
			delete unitManager[i];
			unitManager[i] = nullptr;
		}

		if (mpAnimation != nullptr)
		{
			delete mpAnimation;
		}
	}
}

void UnitManager::initUnitManager()
{
	if (unitManager.empty() && mpAnimation == nullptr) 
	{
		return;
	}
	else 
	{
		unitManager.clear();
		mpAnimation = nullptr;
	}
}

void UnitManager::addUnit(Unit* addUnit)
{
	//add new unit to vector
	unitManager.push_back(addUnit);
	return;
}

void UnitManager::deleteUnit(int x, int y)
{
	//CURRENTLY NOT WORKING
	//Code to delete the smurf you click on

	//vectors to hold the possible x and y positions
	/*vector<int> xPos = { x-8, x-7, x-6, x-5, x-4, x-3, x-2, x-1, x, x+1, x+2, x+3, x+4, x+5, x+6, x+7, x+8 };
	vector<int> yPos = { y-8, y-7, y-6, y-5, y-4, y-3, y-2, y-1, x, y+1, y+2, y+3, y+4, y+5, y+6, y+7, y+8 };

	for (unsigned int i = 0; i < unitManager.size(); i++)
	{
		for(unsigned int j = 0; j < xPos.size(); j++)
		{
			if (unitManager[i]->getPositionX() == xPos[j])
			{
				cout << "x works";
				for(unsigned int h = 0; h < yPos.size(); h++)
				{
					if (unitManager[i]->getPositionY() == yPos[h])
					{
						cout << "y works";
						unitManager.erase(unitManager.begin() + i);
					}
				}
			}
		}
	}*/

	if(unitManager.empty())
	{
		return;
	}
	else
	{
		unitManager.pop_back();
	}
}

Unit* UnitManager::getUnit()
{
	if (!unitManager.empty()) 
	{
		return unitManager.back();
	}
	else if(unitManager.empty())
	{
		return nullptr;
	}
	else 
	{
		return nullptr;
	}
}

void UnitManager::update(double _deltaTime)
{
	if (!unitManager.empty())
	{
		for (unsigned int i = 0; i < unitManager.size(); i++)
		{
			unitManager[i]->update(_deltaTime);
		}
	}
	else if(unitManager.empty())
	{
		return;
	}
}

void UnitManager::draw(GraphicsSystem* mSys)
{
	if (!unitManager.empty())
	{
		for (unsigned int i = 0; i < unitManager.size(); i++)
		{
			unitManager[i]->draw(mSys);
		}
	}

	return;
}
