/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#include "Color.h"

Color::Color() 
{
	this->makeAlColor(1, 1, 1, 1);
}

Color::Color(int r, int g, int b, int a /*= 255*/) 
{
	this->makeAlColor(float(r) / 255.0f, float(g) / 255.0f, float(b) / 255.0f, float(a) / 255.0f);
}

Color::Color(float r, float g, float b, float a /*= 1.0f*/) 
{
	this->makeAlColor(r, g, b, a);
}


void Color::makeAlColor(float r, float g, float b, float a) 
{
	mR = r;
	mG = g;
	mB = b;
	mA = a;
	mAlColor = al_map_rgba_f(r, g, b, a);
}



Color::~Color() 
{
}