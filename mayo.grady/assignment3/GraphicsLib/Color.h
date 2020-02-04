#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/
#include <Trackable.h>

class Color : public Trackable
{
private:
	int mR;
	int mG;
	int mB;
public:
	//Default Constructor
	Color();

	//Constructor
	Color( int rValue, int gValue, int bValue );

	//Destructor
	~Color();

	//Accessors
	int getRValue() { return mR; };
	int getGValue() { return mG; };
	int getBValue() { return mB; };
};