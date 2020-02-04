/*
Conner Root
EGP 310-01
*/

#pragma once

#include "GraphicsLib.h"

class Color : public Trackable
{
	friend class GraphicsSystem;
	friend class GraphicsBuffer;

private:
	int mR, mG, mB, mA;
	ALLEGRO_COLOR getColor();

public:
	// Constructor
	Color();
	Color(int, int, int, int=255);

	// Accessors
	int getR() { return mR; }
	int getG() { return mG; }
	int getB() { return mB; }
	int getA() { return mA; }

	// Destructor
	~Color();
};