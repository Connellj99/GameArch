#pragma once
#include <vector>
#include <iostream>

#include <Trackable.h>

#include "BufferFlags.h"

#include "Color.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Animation.h"
#include "Unit.h"
#include "GraphicsSystem.h"

using namespace std;

class UnitManager :public Trackable 
{
private:

	//vector to hold all the created units
	vector<Unit*> unitManager;

	//Animation
	Animation* mpAnimation;


public:

	//default constructor
	UnitManager();

	//destructor
	~UnitManager();

	//cleanup function
	void cleanup();

	//init to initialize the manager
	void initUnitManager();

	//add unit to the manager
	void addUnit(Unit* addUnit);

	//delete unit from the manager
	void deleteUnit(int x, int y);

	//get the last unit from the manager
	Unit* getUnit();

	//update function
	void update(double _deltaTime);

	//draw function
	void draw(GraphicsSystem* mSys);

};