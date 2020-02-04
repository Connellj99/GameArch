/*
Author: Steven Pershyn
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is my own work, except where I referenced classmates' work and mentioned where relevant.
*/
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

