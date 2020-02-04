#pragma once
/*
Author: Amelia Payne
Class: EGP-310 <2> 
Assignment: pa 3
Certification of Authenticity: 
I certify that this assignment is entirely my own work.
*/

/*
This struct represents a rgb color 
*/
struct Color : public Trackable 
{
	int r;
	int g;
	int b;

	/*
	Create a new color with the values given
	*/
	Color(int rA, int bA, int gA)
	{
		r = rA;
		g = gA;
		b = bA;
	}
};