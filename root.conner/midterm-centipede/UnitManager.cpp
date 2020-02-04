/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include <PerformanceTracker.h>

#include "UnitManager.h"
#include "EventSystem.h"
#include "ScoreEvent.h"
#include "DeathEvent.h"
#include "ChangeSpeedEvent.h"

// Constructor
UnitManager::UnitManager()
{
}

// Init
void UnitManager::init()
{
	mDispW = 720;
	mDispH = 768;
	mpPlayer = new Unit(351, 710, mpPlayerAnim);
	
	mpBullet = new Bullet(0, 760, -5, mpBulletAnim, 20);
	mpBullet->setParent(mpPlayer);
	
	setUnits();
}
void UnitManager::init(int w, int h)
{
	mDispW = w;
	mDispH = h;

	mpPlayer = new Unit(mDispW / 2, mDispH - 20, mpPlayerAnim);

	mpBullet = new Bullet(0, mDispH, -5, mpBulletAnim, 20);
	mpBullet->setParent(mpPlayer);

	setUnits();
}
void UnitManager::setUnits()
{
	mpPlayer->setLocation(mDispW / 2, mDispH - 20);

	mpBullet->reset();

	generateMushrooms();
	generateCentipede();
}

// Add animation
void UnitManager::addAnim(GraphicsBuffer* gB, int wdth, int hght, float sp, bool loop)
{
	// Add up to two animations
	if (mpPlayerAnim == nullptr)
		mpPlayerAnim = new Animation(gB, wdth, hght, sp, loop);
	else if (mpMushroomAnim == nullptr)
		mpMushroomAnim = new Animation(gB, wdth, hght, sp, loop);
	else if (mpBulletAnim == nullptr)
		mpBulletAnim = new Animation(gB, wdth, hght, sp, loop);
	else if (mpCentipedeHeadAnim == nullptr)
		mpCentipedeHeadAnim = new Animation(gB, wdth, hght, sp, loop);
	else if (mpCentipedeBodyAnim == nullptr)
		mpCentipedeBodyAnim = new Animation(gB, wdth, hght, sp, loop);
}

// Add units
void UnitManager::generateMushrooms()
{
	for (int a = 0; a < 20; a++)
	{
		int x = rand() % 700 + 0;
		int y = rand() % 550 + 24;

		addMushroom(x, y);
	}
}
void UnitManager::addMushroom(int xPos, int yPos)
{
	// Round to nearest 24
	xPos -= xPos % 24;
	yPos -= yPos % 24;

	Unit* pTempMush = new Unit(xPos, yPos, mpMushroomAnim);
	pTempMush->setLocation(xPos, yPos);
	mpMushroomList.push_back(pTempMush);
}

void UnitManager::generateCentipede()
{
	Segment* pTempSegment;
	int x = mDispW / 2;

	for (int a = 0; a < 7; a++)
	{
		int y = 0 - (a * 24);

		pTempSegment = new Segment(x, y, mBaseCentSpeed+ mSpeedIncrease, mDispW, mDispH, mpCentipedeBodyAnim);

		mpCentipede.push_back(pTempSegment);
	}

	mpCentipede[0]->setAnimation(mpCentipedeHeadAnim);
}

// Accessor
Unit* UnitManager::getUnit()
{
	return mpMushroomList[mpMushroomList.size() - 1];
}

// Other Functions
void UnitManager::speedUpCentipede(float a)
{
	for each(Segment* s in mpCentipede)
		s->speedUp(a);
}

void UnitManager::increaseDifficulty(float a)
{ 
	mSpeedIncrease += a;
	generateCentipede();
}

void UnitManager::resetAllUnitStates()
{
	// Reset everything
	mSpeedIncrease = 0;
	deleteAllUnits();

	// Create everything again
	setUnits();
}

// Update Functions
void UnitManager::updateUnits()
{
	mpPlayer->update();

	mpBullet->update();

	for each (Unit* u in mpMushroomList)
	{
		u->update();
	}

	for each (Segment* s in mpCentipede)
	{
		s->update();
	}

	detectSegmentCollision();

	if ((int)mpCentipede.size() <= 0)
		EventSystem::getInstance()->fireEvent(ChangeSpeedEvent(1));
}

void UnitManager::drawUnits()
{
	mpBullet->draw();

	mpPlayer->draw();

	for each (Unit* u in mpMushroomList)
	{
		u->draw();
	}

	for each (Segment* s in mpCentipede)
	{
		s->draw();
	}
}

// Find Collisions
void UnitManager::detectSegmentCollision()
{
	// Detect collision btwn segments and mushrooms
	for (int i = 0; i < (int)mpCentipede.size(); i++)
	{
		for (int j = 0; j < (int)mpMushroomList.size(); j++)
		{
			if (!mpCentipede[i]->getMovingDown())
				if ((abs(mpMushroomList[j]->getXPos() - mpCentipede[i]->getXPos()) < 23) &&
					(abs(mpMushroomList[j]->getYPos() - mpCentipede[i]->getYPos()) < 23))
					mpCentipede[i]->collide();
		}
	}

	// Detect collision btwn centipede and player
	for (int i = 0; i < (int)mpCentipede.size(); i++)
	{
		int xDist = mpPlayer->getXPos() - mpCentipede[i]->getXPos();
		if ((xDist > -21 && xDist < 24) &&
			(abs(mpPlayer->getYPos() - mpCentipede[i]->getYPos()) < 24))
			EventSystem::getInstance()->fireEvent(DeathEvent());
	}
}

// Delete units
void UnitManager::deleteUnit(int x, int y)
{
	// Destroy Segment
	for (int i = 0; i < (int)mpCentipede.size(); i++)
	{
		if (abs(mpCentipede[i]->getXPos() - x + 12) < 12 && abs(mpCentipede[i]->getYPos() - y + 12) < 12)
		{
			// Fire score event
			if (mpCentipede[i]->getIsHead())
				EventSystem::getInstance()->fireEvent(ScoreEvent('h'));
			else
				EventSystem::getInstance()->fireEvent(ScoreEvent('b'));

			// Set next segment as head
			if (i + 1 < (int)mpCentipede.size())
			{
				mpCentipede[i + 1]->setAnimation(mpCentipedeHeadAnim);
				mpCentipede[i + 1]->setHead();
			}

			// Delete segment
			delete mpCentipede[i];
			mpCentipede.erase(mpCentipede.begin() + i);

			// Reset bullet
			mpBullet->reset();

			// Create Mushroom
			addMushroom(x, y);

			// Speed up centipede
			speedUpCentipede(0.6);

			// Break out so only one thing can get deleted
			return;
		}
	}

	// Destroy Mushroom
	for (int i = 0; i < (int)mpMushroomList.size(); i++)
	{
		if (abs(mpMushroomList[i]->getXPos() - x + 12) < 12 && abs(mpMushroomList[i]->getYPos() - y + 12) < 12)
		{
			mpMushroomList[i]->getHit();

			if (mpMushroomList[i]->getHealth() <= 0)
			{
				delete mpMushroomList[i];
				mpMushroomList.erase(mpMushroomList.begin() + i);

				// Fire score event
				EventSystem::getInstance()->fireEvent(ScoreEvent('m'));
			}

			mpBullet->reset();
		}
	}
}

void UnitManager::deleteAllUnits()
{
	int size = (int)mpMushroomList.size();
	for (int i = 0; i < size; i++)
	{
		delete mpMushroomList[0];
		mpMushroomList.erase(mpMushroomList.begin());
	}

	size = (int)mpCentipede.size();
	for (int i = 0; i < size; i++)
	{
		delete mpCentipede[0];
		mpCentipede.erase(mpCentipede.begin());
	}
}

UnitManager::~UnitManager() 
{ 
	delete mpPlayerAnim;
	delete mpCentipedeHeadAnim;
	delete mpCentipedeBodyAnim;
	delete mpBulletAnim;
	delete mpMushroomAnim;

	delete mpPlayer;
	delete mpBullet;

	deleteAllUnits(); 
}