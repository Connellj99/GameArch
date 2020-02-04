#include "SnakeManager.h"
#include "EventSystem.h"
#include "GameEvent.h"
#include "Event.h"
#include "Game.h"

SnakeManager::SnakeManager()
{
	
}

SnakeManager::~SnakeManager()
{
}

void SnakeManager::init(Unit piece, int startSeg)
{
	mStartSeg = startSeg;
	mCurrentSegMove = 0;
	mTargetMoveTime = 200;
	mDirection = 0;
	mSegment = piece;
	mSnakeVector.clear();
	mSnakeVector.push_back(piece);
	for (int i = 1; i < startSeg; i++)
	{
		addSegment();
	}

}

void SnakeManager::addSegment()
{
	mSnakeVector.push_back(mSegment);
}

void SnakeManager::draw()
{
	for (int i = 0; i < mSnakeVector.size(); i++)
	{
		mSnakeVector[i].draw();
	}
}

void SnakeManager::update(float frameTime)
{

	mCurrentTime -= frameTime;
	if (mCurrentTime <= 0)
	{
		
		mCurrentSegMove++;
		mCurrentTime = mTargetMoveTime;
		if (mSnakeVector.size() > 2)
		{
			for (int i = mSnakeVector.size()-1; i > 0; i--)
			{
				mSnakeVector[i].updateLocation(mSnakeVector[i - 1].getPosition());
			}
		}
		
		head();
		checkForCollision();
	}

	
}

void SnakeManager::head()
{
	switch (mDirection)
	{
	case 0:
		mSnakeVector[0].updateLocation(Vector2D(mSnakeVector[0].getPosition().getX(), mSnakeVector[0].getPosition().getY() - 50));
		break;
	case 1:
		mSnakeVector[0].updateLocation(Vector2D(mSnakeVector[0].getPosition().getX()+50, mSnakeVector[0].getPosition().getY()));
		break;
	case 2:
		mSnakeVector[0].updateLocation(Vector2D(mSnakeVector[0].getPosition().getX(), mSnakeVector[0].getPosition().getY() + 50));
		break;
	case 3:
		mSnakeVector[0].updateLocation(Vector2D(mSnakeVector[0].getPosition().getX()-50, mSnakeVector[0].getPosition().getY()));
		break;
	}
}

void SnakeManager::checkForCollision()
{
	//Chek out of bounds
	if (mSnakeVector[0].getPosition().getX() < 0 || mSnakeVector[0].getPosition().getX() > 800)
	{
		Game::getInstance()->hasLost();
	}
	if (mSnakeVector[0].getPosition().getY() < 0 || mSnakeVector[0].getPosition().getY() > 800)
	{
		Game::getInstance()->hasLost();
	}
	//Check body segments
	for (int i =1; i < mSnakeVector.size(); i++)
	{
		if (mSnakeVector[i].getPosition() == mSnakeVector[0].getPosition())
		{
			Game::getInstance()->hasLost();
		}
	}
	//check external stuff
	Game::getInstance()->checkCollision(mSnakeVector[0].getPosition());
}
