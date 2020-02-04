#include "SnakeManager.h"
const int rangeX = 40;
const int rangeY = 40;



SnakeManager::SnakeManager() 
{
	mSnake = new Snake();
}

SnakeManager::~SnakeManager()
{
	cleanUp();
}

void SnakeManager::drawAll()
{
	//mSnake->drawSnake();
}

void SnakeManager::cleanUp()
{
	delete mSnake;
}

void SnakeManager::setX(int x)
{
	mSnake->setX(x);
}

void SnakeManager::setY(int y)
{
	mSnake->setY(y);
}

int SnakeManager::getX()
{
	return mSnake->getX();
}

int SnakeManager::getY()
{
	return mSnake->getY();
}

int SnakeManager::getSize()
{
	return mSnake->getSize();
}