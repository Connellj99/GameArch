/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#pragma once
#include <System.h>
#include "Unit.h"
#include <list>
#include <Trackable.h>

class UnitManager : public Trackable
{

private:
	std::list<Unit *> mUnits;
	bool mIsInit = false;

public:
	/*
	Create unitManager and set mIsInit to true
	*/
	UnitManager();

	/*
	Destroy the unit manager if it has been inited
	*/
	~UnitManager();

	/*
	Add a new unit to the end of the list
	*/
	void add(Unit * unit);

	/*
	Remove all units from the list and delete them. Sets isInit to false so things aren't deleted twice
	*/
	void clear();

	/*
	Call Update on each unit in the list of units
	*/
	void update(double deltaTime);

	/*
	Draw each unit to the screen. Takes a pointer to the system
	*/
	void draw(System * system);

	/*
	Set if a given unit should animate
	*/
	void setIsAnimating(bool isAnimating);

	/*
	Delete all units at a position pos
	*/
	void deleteAtPosition(Position pos);

	/*
	Get the last unit in the list
	*/
	Unit* getLastUnit();
};
