#include "Color.h"

Color::Color()
{
	R = 0;
	G = 0;
	B = 0;
}

Color::Color(int r, int g, int b)
{
	R = r;
	G = g;
	B = b;
}


Color::~Color()
{
}

int Color::getR()
{
	return R;
}

int Color::getG()
{
	return G;
}

int Color::getB()
{
	return B;
}

