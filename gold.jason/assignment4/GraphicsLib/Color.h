/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 3											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

/// <summary>
///		A color.
/// </summary>
/// <seealso cref="Trackable" />
class Color :
	public Trackable
{
public:
	// Initialize a default white color.
	Color();

	// Create a color with the given values.
	Color(int _r, int _g, int _b);

	// Clean up the color instance.
	~Color();

	// Get the red value.
	int getR();

	// Get the green value.
	int getG();

	// Get the blue value.
	int getB();

private:
	// Red
	int mR = 0;

	// Green
	int mG = 0;

	// Blue
	int mB = 0;
};