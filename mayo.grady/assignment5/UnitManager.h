#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 4
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Trackable.h"
#include "Unit.h"
#include <string>
#include <vector>

class Unit;

const int RADIUS = 30;

class UnitManager : public Trackable
{
private:
	//collection of units
	std::vector<Unit*> mvCollection;

public:
	//constructor
	UnitManager();

	//destructor
	~UnitManager();

	//add a unit
	void add(Vector2D position);

	//delete a unit
	void remove(Vector2D position);

	//get units
	Unit * getUnit(int index);

	//clear all units, remove and delete
	void cleanup();

	//update units
	void update(double dT);

	//draw units
	void draw();

	//get vector size
	int getCollectionSize();

	//toggle animation
	void toggleAnim();
};