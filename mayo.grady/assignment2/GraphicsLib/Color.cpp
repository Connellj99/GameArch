/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 2
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Color.h"

Color::Color()
{
	this->mR = 0;
	this->mG = 0;
	this->mB = 0;
}

Color::Color( int rValue, int gValue, int bValue )
{
	this->mR = rValue;
	this->mG = gValue;
	this->mB = bValue;
}

Color::~Color()
{

}