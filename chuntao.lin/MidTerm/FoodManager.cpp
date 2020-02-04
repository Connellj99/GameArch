#include "FoodManager.h"

FoodManager::FoodManager()
{
	mTargetTime = 60;
	mTimeElapsed = mTargetTime;
	mCurrentIndex = 0;
}

FoodManager::~FoodManager()
{
	removeAndDestroyAllFruits();
}

Unit FoodManager::getUnit(int index)
{
	return *mFruits[index];
}

int FoodManager::getSize()
{
	return mFruits.size();
}

Vector2 FoodManager::getTargetPos(int index)
{
	return mFruits[index]->mCurrentLocation;
}

void FoodManager::spawnFruit(Animation * animationOne, Animation * animationTwo)
{
	createFruit(Vector2(300,150));

	// add both animations to the unit, the dean and smurf.
	addAnimation(getSize() - 1, *animationOne);
	addAnimation(getSize() - 1, *animationTwo);
}

void FoodManager::spawnFruit(Animation * animationOne)
{
	createFruit(Vector2(300, 150));

	// add both animations to the unit, the dean and smurf.
	addAnimation(getSize() - 1, *animationOne);
}

void FoodManager::createFruit(Vector2 newPos)
{
	mFruits.push_back(new Unit(newPos));
}

void FoodManager::destroyFruit(int index)
{
	delete mFruits[index];
	mFruits.erase(mFruits.begin() + index);;
}

void FoodManager::removeAndDestroyAllFruits()
{
	for (int i = 0, max = mFruits.size(); i < max; i++)
	{
		delete mFruits[i];
	}
	mFruits.clear();
}

void FoodManager::addAnimation(int index, Animation & newAnim)
{
	mFruits[index]->setAnimation(newAnim);
}

void FoodManager::swapAnimations(int index)
{
	// Is the given index within bounds?
	if (index > -1 && index < getSize())
	{
		// If yes, then swap the animation at the given index
		mFruits[index]->swapAnimation();
	}
}

void FoodManager::setFruitPos()
{
	//assign a random vector2 position for the fruit to move too
	srand(time(NULL));
	mFruitPos = Vector2(rand() % (650 - 50) + 50, rand() % (500 - 50) + 50);
}

void FoodManager::moveFruit()
{
	mFruits[0]->mCurrentLocation = mFruitPos;
}

void FoodManager::updateFood(double timeBetweenFrames)
{
	for (int i = 0, max = mFruits.size(); i < max; i++)
	{
		mFruits[i]->update(timeBetweenFrames);
	}
}

void FoodManager::drawFood()
{
	for (int i = mFruits.size(); i > 0; i--)
	{
		mFruits[i-1]->draw("grow");
	}
}
