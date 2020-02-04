/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include "System.h"
#include "Unit.h"
class UnitManager : public Trackable
{
public:
	UnitManager();
	~UnitManager();

	void addUnit(Unit* unit);
	int getUnitIndex(Unit* unit);
	void removeUnit(Unit* unit);
	void removeUnit(int index);
	Unit* getUnit(int index);
	Unit* getLast() { return mUnits.back(); };
	void clear();
	int getNumUnits() { return mUnits.size(); };
	void deleteUnitAt(Point);

	void update(double);

	void draw();

private:
	vector<Unit*> mUnits;
};