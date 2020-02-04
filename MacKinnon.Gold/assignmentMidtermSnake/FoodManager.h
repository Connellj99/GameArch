#pragma once
#include "Unit.h"
#include "UnitManager.h"

class FoodManager : public Trackable
{
public:
	FoodManager();
	~FoodManager();

	Unit getUnit(int index);

	void createFood(Vector2D pos);
	void destroyFood(int index);
	void deleteAllFood();
	void addAnimation(Animation &animation, int index);

	void update(double time);
	void draw();


private:
	std::vector<Unit*> mpFood;

	Vector2D mFoodPosition;
	int mCurrentIndex;
};

