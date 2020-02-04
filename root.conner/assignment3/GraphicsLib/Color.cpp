/*
Conner Root
EGP 310-01
*/

#include "Color.h"

Color::Color()
{
	mR = 255;
	mG = 255;
	mB = 255;
	mA = 255;
}
Color::Color(int r, int g, int b, int a)
{
	mR = r;
	mG = g;
	mB = b;
	mA = a;
}

ALLEGRO_COLOR Color::getColor()
{
	return al_map_rgba(mR, mG, mB, mA);
}

// Destructor
Color::~Color()
{
}