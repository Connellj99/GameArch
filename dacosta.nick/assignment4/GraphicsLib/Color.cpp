/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include "Trackable.h"

#include "Color.h"

// Create a base color.
Color::Color()
{
	return;
}

// Create a color with the given values.
Color::Color(int _r, int _g, int _b)
{
	// Set the color values.
	mR = _r;
	mG = _g;
	mB = _b;

	return;
}

// Clean up the color instance.
Color::~Color()
{
	return;
}

// Get the red value.
int Color::getR()
{
	return mR;
}

// Get the green value.
int Color::getG()
{
	return mG;
}

// Get the blue value.
int Color::getB()
{
	return mB;
}