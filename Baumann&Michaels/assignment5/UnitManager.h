#pragma once
#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include "Trackable.h"
#include "Unit.h"
#include <vector>
#include <map>

class Unit;

using namespace std;

class UnitManager :public Trackable
{
private:
	bool mCleanedUp = false;

	map<string, Unit*> mUnits;
	vector<Unit*> mAlwaysCreate;
	vector<Unit*> mUnitStorage;
public:
	UnitManager();
	~UnitManager();
	void addUnit(string unitName, Unit* unit);
	void addAlwaysCreate(string unitName);
	void addAlwaysCreate(Unit* unit);
	void addToStorage(string unitName);
	void addToStorage(Unit* unit);
	void removeFromStorage(Unit* unit);
	void instantiateAtMouse(bool mouseDown, int* CurrentMousePos, System* drawingSystem, int offset);
	void swapFrozen();
	void removeAtCoords(int* coords);
	void incrementLastSpriteAnimation();
	void deleteUnit(string unitName);
	Unit* getUnit(string unitName);
	void clear();
	void update(double elapsedTime);
	void cleanup();
	void draw(System* drawingSystem, float scale, int offset);
};

#endif // !UNITMANAGER_H
