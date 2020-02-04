#pragma once
#include <vector>
#include <list>
#include "Unit.h"
#include "TileTypes.h"
#include "Trackable.h"

class SnakeUnit : public Trackable
{
public:
	SnakeUnit();
	~SnakeUnit();

	void add(Unit* endUnit);
	void update(double time, std::vector<std::vector<TileTypes>> &grid);
	void draw(System* system, int cellHeight, int cellWidth);

	Unit* getHead();
	Unit* getTail();
	int getSnakeSize();

	void setDer(int x, int y);
	void setSpeed(float speedChangeAmount);
	void setStartSpeed(float startSpeed);

	void cleanup();

private:
	std::list<Unit*> mpUnits;
	//std::vector<Unit*> mpUnits;
	bool mIsInit;
	int mXMove = 1;
	int mYMove = 0;
	int mHeadDerX = 1;
	int mHeadDerY = 0;
	float mTimeCounter = 0;
	float mSpeed = 0.2;
};

