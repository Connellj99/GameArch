/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#pragma once

/*
This struct stores an 2D position
*/
struct Position : public Trackable
{
	//Member varibles
	int x;
	int y;


	//Default constructor
	Position()
	{
		x = 0;
		y = 0; 
	};

	/*
	Constructor that takes two ints x and y
	*/
	Position(int xA, int yA) 
	{
		x = xA;
		y = yA;
	}

};