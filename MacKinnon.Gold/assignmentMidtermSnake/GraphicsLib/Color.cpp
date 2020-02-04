#include "Color.h"


//default constructor for color
Color::Color()
{
	mR = 0;
	mG = 0;
	mB = 0;
}

//main constructor for color
Color::Color(int r, int g, int b) 
{
	this->mR = r;
	this->mG = g;
	this->mB = b;
}

//deconstructor for color
Color::~Color()
{
}

int Color::getB() 
{
	return mB;
}

int Color::getG() 
{
	return mG;
}

int Color::getR() 
{
	return mR;
}
