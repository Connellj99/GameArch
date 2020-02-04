#pragma once
#include "Trackable.h"
#include <string>
#include <iterator>
#include <vector>
#include "Sprite.h"

class Unit;
class Animation;
class System;

class UnitManager : public Trackable		//A class to hold a “map” (dictionary) or “list” of all Units in the game
{
public:

	UnitManager();
	//UnitManager();
	~UnitManager();

	Unit* getUnit(int index) { return mpUnits[index]; };
	

	void addUnit(Unit* object);
	void deleteUnit(int pointX, int pointY, int size);
	void deleteUnit();

	void clearAllUnits();

	void createNewUnit(Animation* startAnim, int posX, int posY);
	void createNewMushroom(std::vector<Sprite> sprites, int x, int y);
	void createNewBullet(Sprite* image, int x, int y);
	void createNewCentipedePart(Sprite* image, int x, int y, int speed);

	void update(double frames);
	void draw(System* systemObject);

	void disableAnimation();

	void switchHead(Animation* anim, Animation* otherAnim);

	int getNumUnitsOfType(std::string id);

private:

	static int mCounter;
	
	

	//Map of units
	std::vector<Unit*> mpUnits;
};