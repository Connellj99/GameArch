/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/


#include "Game.h"


int main()
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	gpGame->init(WINDOW_WIDTH, WINDOW_HEIGHT);



	gpGame->runGame();



	gpGame->cleanUp();

	delete gpGame;


	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");

	return 0;

}