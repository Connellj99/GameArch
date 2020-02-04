#ifndef POWERUP_MANAGER_H
#define POWERUP_MANAGER_H

#include "Unit.h"
#include "UnitManager.h"

class FoodManager : public Trackable
{
public:

	// Constructors
	FoodManager();

	// Destuctors
	~FoodManager();

	// Acessors
	Unit getUnit(int index);
	int getSize();
	Vector2 getTargetPos(int index);
	Vector2 getVariablePos() { return mFruitPos; }

	// Initializers
	void spawnFruit(Animation* animationOne, Animation* animationTwo);//used to spawn fruit if we wanted two
	void spawnFruit(Animation* animationOne);//used to spawn fruit with one animation. This is the one I use.

	// Mutators
	void createFruit(Vector2 newPos);
	void destroyFruit(int index);
	void removeAndDestroyAllFruits();
	void addAnimation(int index, Animation & newAnim);
	void swapAnimations(int index);
	void setFruitPos();
	void moveFruit();

	// Game Loop Functions
	void updateFood(double timeBetweenFrames);
	void drawFood();

private:

	// Vectors
	vector<Unit*> mFruits;

	Vector2 mFruitPos;
	double mTimeElapsed = 0;
	double mTargetTime = 60;
	int mCurrentIndex = 0;
};
#endif