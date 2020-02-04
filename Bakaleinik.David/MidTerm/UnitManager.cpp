#include "UnitManager.h"
#include "Unit.h"
#include "Mushroom.h"
#include "Animation.h"
#include "System.h"
#include "Projectile.h"
#include "Game.h"
#include "Player.h"
#include "Centipede.h"
#include "FileReader.h"

int UnitManager::mCounter = 0;

UnitManager::UnitManager()
{
	
}

UnitManager::~UnitManager()
{
	clearAllUnits();
}

void UnitManager::addUnit(Unit* object)
{
	mpUnits.push_back(object);
}

void UnitManager::deleteUnit(int pointX, int pointY, int size) //iterate through map and ask each unit if it needs to be deleted through checkCollision()
{
	for (vector<Unit*>::iterator itr = mpUnits.begin(); itr != mpUnits.end(); itr++)
	{
		if ((*itr)->checkCollision(pointX, pointY, size))
		{
			if ((*itr)->getID() == "Projectile")
			{
				
				delete *itr;
				mpUnits.erase(itr);
				return;
				
			}
			
		}
	}
}

void UnitManager::deleteUnit()
{

}

void UnitManager::clearAllUnits()
{
	for(vector<Unit*>::iterator itr = mpUnits.begin(); itr != mpUnits.end(); itr++)
	{ 
		delete *itr;
		
	}
	mpUnits.clear();
}

//Go through the map and call each unit's update()
void UnitManager::update(double frames)
{
	
	std::vector<Unit*> forDeletion;
	
	for (vector<Unit*>::iterator itr = mpUnits.begin(); itr != mpUnits.end(); itr++)
	{
 		
		if ((*itr)->getID() == "Projectile")
		{
			bool noHit = true;
			Projectile* theBullet = static_cast<Projectile*>((*itr));
			if (theBullet->getYloc() < 0)
			{
				noHit = false;
				(*itr)->changeState();
				forDeletion.push_back((*itr));
			}

			for (vector<Unit*>::iterator itr2 = mpUnits.begin(); itr2 != mpUnits.end(); itr2++)
			{
				if ((*itr2) != theBullet && (*itr2)->checkCollision(theBullet->getXloc(), theBullet->getYloc(), 25))
				{
					
					noHit = false;
					//std::cout << "Hit";

					if ((*itr2)->getID() == "Mushroom")
					{
						Mushroom* theMushroom = static_cast<Mushroom*>((*itr2));
						theMushroom->looseHP();

						if (theMushroom->getHP() == 0)
						{
							Game::getInstance()->addScore(10);
							Game::getInstance()->getPlayer()->addLifeScore(10);
							
							(*itr2)->changeState();
							forDeletion.push_back((*itr2));
						}

						(*itr)->changeState();
						forDeletion.push_back((*itr));
					}
					else if ((*itr2)->getID() == "Centipede")
					{
						(*itr2)->changeState();
						forDeletion.push_back((*itr2));

						Game::getInstance()->addScore(100);
						Game::getInstance()->getPlayer()->addLifeScore(100);

						createNewMushroom(Game::getInstance()->getMushrooms(), (*itr2)->getXloc(), (*itr2)->getYloc());

						(*itr)->changeState();
						forDeletion.push_back((*itr));

						for (vector<Unit*>::iterator itr3 = mpUnits.begin(); itr3 != mpUnits.end(); itr3++)
						{

							if ((*itr3)->getID() == "Centipede")
							{
								Centipede* theCenti = static_cast<Centipede*>((*itr3));
								theCenti->increaseSpeedByAmount(1);
							}
						}

					}

					break;
				}
			}

			if (noHit)
			{ 
				(*itr)->update(frames);
			}
		}

		else if ((*itr)->getID() == "Centipede")
		{
			Centipede* theCenti = static_cast<Centipede*>((*itr));

			if (theCenti->getXloc() < 0 || theCenti->getXloc() > 800) // 600 is the defaule screen width. In the future (aka, if I had more time) this would be data you could get from Game
			{
				theCenti->changeDirection();

				theCenti->dropDown();
			}

			if (theCenti->getYloc() > 500)
			{
				theCenti->changeDirection();
				theCenti->partialReset();
			}

			for (vector<Unit*>::iterator itr2 = mpUnits.begin(); itr2 != mpUnits.end(); itr2++)
			{
				if ((*itr2) != theCenti && (*itr2)->checkCollision(theCenti->getXloc(), theCenti->getYloc(), 25))
				{

					if ((*itr2)->getID() == "Mushroom")
					{
						theCenti->changeDirection();
						theCenti->dropDown();
					}

					break;
				}
				/*else if ((*itr2)->getID() == "Player")
				{
					Player* thePlayer= static_cast<Player*>((*itr));

					thePlayer->looseLife();
				}*/
			}

			(*itr)->update(frames);

		}
		else
		{
			(*itr)->update(frames);
		}
		
	}

	for (vector<Unit*>::iterator itrI = forDeletion.begin(); itrI != forDeletion.end(); itrI++)
	{
		for (vector<Unit*>::iterator itrJ = mpUnits.begin(); itrJ != mpUnits.end(); itrJ++)
		{
			if((*itrJ)->getState())
			{
				delete *itrJ;
				mpUnits.erase(itrJ);
				break;
			}
			
		}
	}

	if (getNumUnitsOfType("Centipede") == 0)
	{
		Game::getInstance()->createNewCentipede(2);
	}

}

int UnitManager::getNumUnitsOfType(std::string id)
{
	int mCount = 0;
	for (vector<Unit*>::iterator itr = mpUnits.begin(); itr != mpUnits.end(); itr++)
	{
		if ((*itr)->getID() == id)
		{
			mCount++;
		}
	}

	return mCount;
}

//Go through the map and call every unit's draw()
void UnitManager::draw(System* systemObject)
{
	for (vector<Unit*>::iterator itr = mpUnits.begin(); itr != mpUnits.end(); itr++)
	{
		(*itr)->drawUnit(systemObject);
	}
}

void UnitManager::createNewUnit(Animation* startAnim, int posX, int posY)
{
	Unit* newUnit = new Unit(startAnim, posX, posY);
	
	mCounter++;
	

	addUnit(newUnit);
}

void UnitManager::createNewMushroom(std::vector<Sprite> sprites, int x, int y)
{
	Mushroom* newMushroom = new Mushroom(sprites, x, y);

	mCounter++;

	addUnit(newMushroom);
}

void UnitManager::createNewBullet(Sprite* image, int x, int y)
{
	Projectile* bullet = new Projectile(image, x, y);
	
	mCounter++;

	addUnit(bullet);
}

void UnitManager::createNewCentipedePart(Sprite* image, int x, int y, int speed)
{
	Centipede* segment = new Centipede(image, x, y, speed);

	mCounter++;

	addUnit(segment);
}

void UnitManager::disableAnimation()
{
	for (vector<Unit*>::iterator itr = mpUnits.begin(); itr != mpUnits.end(); itr++)
	{
		(*itr)->toggleAnimation();
	}
}

void UnitManager::switchHead(Animation* anim, Animation* otherAnim)
{
	
		if (mpUnits.size() >= 1)
		{

			if (getUnit(mpUnits.size() - 1)->getUnitAnimation().getAnimID() != anim->getAnimID())
			{
				getUnit(mpUnits.size()-1)->setUnitAnimation(anim);
				return;
			}
			else
			{
				getUnit(mpUnits.size()-1)->setUnitAnimation(otherAnim);
			}
		}
	
}
