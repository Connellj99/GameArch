#include "FoodManager.h"



FoodManager::FoodManager()
{
	mCurrentIndex = 0;
}


FoodManager::~FoodManager()
{
	deleteAllFood();
}

Unit FoodManager::getUnit(int index)
{
	return *mpFood[index];
}

void FoodManager::spawnFood(Animation * animation)
{

}
