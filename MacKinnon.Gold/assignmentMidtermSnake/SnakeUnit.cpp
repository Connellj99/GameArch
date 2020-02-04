#include "SnakeUnit.h"
#include "Game.h"


SnakeUnit::SnakeUnit()
{
	mIsInit = true;
}


SnakeUnit::~SnakeUnit()
{
	if (mIsInit) 
	{
		cleanup();
		mIsInit = false;
	}
}
//adds unit to snake
void SnakeUnit::add(Unit * endUnit)
{
	mpUnits.push_back(endUnit);
}
//updates teh position of the snake on the grid
void SnakeUnit::update(double time, std::vector<std::vector<TileTypes>> &grid)
{
	for (Unit* unit : mpUnits)
	{
		unit->update(time);
	}

	 
	mTimeCounter += time;

	/*if (mTimeCounter > mSpeed) //higher speed number slower movement
	{
		mTimeCounter = 0;
		grid[mpUnits.front()->getUnitLocX()][mpUnits.front()->getUnitLocY()] = TileTypes::SNAKE_TILE;

		Unit* tailUnit = getTail();

		grid[tailUnit->getUnitLocX()][tailUnit->getUnitLocY()] = TileTypes::EMPTY_TILE;
		unsigned int x = (getHead()->getUnitLocX() + mHeadDerX);
		unsigned int y = (getHead()->getUnitLocY() + mHeadDerY);

		//part of a system that causes snake to loop back when off screen
		if (x < 0)
		{
			x = grid.size() - 1;
		}
		else if (x >= grid.size())
		{
			x = 0; //x = 0 causes teleport to other side
		}
		if (y < 0)
		{
			y = grid.size() - 1;
		}
		else if (y >= grid.size())
		{
			y = 0;; //y = 0 causes teleport to other side
		}

		tailUnit->setLocation(x, y);

		mpUnits.pop_back();
		mpUnits.push_front(tailUnit);
	}*/
}
//draws snake
void SnakeUnit::draw(System* system, int cellHeight, int cellWidth)
{
	for (Unit* unit : mpUnits)
	{
		unit->draw(system, cellHeight, cellWidth);
	}
}
void SnakeUnit::move(std::vector<std::vector<TileTypes>>& grid)//if keeping this then add variable with start positions of the player and replace the 4 and 3 with start positons
{
	int temp = mpUnits.front()->getUnitLocY();
	int temp2 = mpUnits.front()->getUnitLocX();

	movementSafetyCheck(temp, temp2);

	//grid[mpUnits.front()->getUnitLocX()][mpUnits.front()->getUnitLocY()] = TileTypes::SNAKE_TILE;
	grid[mpUnits.front()->getUnitLocX()][temp] = TileTypes::SNAKE_TILE;

	int bob = mpUnits.front()->getUnitLocX();
	int joe = mpUnits.front()->getUnitLocY();

	Unit* headUnit = getHead();

	//grid[tailUnit->getUnitLocX()][tailUnit->getUnitLocY()] = TileTypes::EMPTY_TILE;
	unsigned int x = (getHead()->getUnitLocX() + mHeadDerX);
	unsigned int y = (getHead()->getUnitLocY() + mHeadDerY);

	headUnit->setLocation(x, y);

	
	mpUnits.push_front(headUnit);
	mpUnits.pop_back();

	grid[bob][joe] = TileTypes::EMPTY_TILE;

}
//gets head unit
Unit * SnakeUnit::getHead()
{
	return mpUnits.front();
}
//gets tail unit
Unit * SnakeUnit::getTail()
{
	return mpUnits.back();
}
//gets snake size
int SnakeUnit::getSnakeSize()
{
	return mpUnits.size();
}

void SnakeUnit::setDer(int x, int y)
{
	if (!(x == -mHeadDerX || y == -mHeadDerY)) 
	{
		mHeadDerX = x;
		mHeadDerY = y;
	}
}
//modifies current speed by speedChangeAmount
void SnakeUnit::setSpeed(float speedChangeAmount)
{
	mSpeed += speedChangeAmount;
}
//sets speed
void SnakeUnit::setStartSpeed(float startSpeed) 
{
	mSpeed = startSpeed;
}
//cleansup snake
void SnakeUnit::cleanup()
{
	for (Unit* unit : mpUnits)
	{
		delete unit;
	}

	mpUnits.clear();
}

void SnakeUnit::movementSafetyCheck(int t, int t2)
{
	if (t < 0 || t2 < 0 || t > 14 || t2 > 14)
	{
		if (t2 < 0 || t2 > 14)
		{
			t2 = 4;
			mpUnits.front()->setUnitLocation(Vector2D(t2, mpUnits.front()->getUnitLocY()));
		}
		else
		{
			t = 3;
			mpUnits.front()->setUnitLocation(Vector2D(mpUnits.front()->getUnitLocX(), t));
		}

	}
}