

/*
Author: David Bakaleinik
Class: EGP-310
Assignment: PA 02
Date Assigned: 01/25/2019 - 12:30pm
Due Date: 02/01/2019 - 12:01pm
Description:
Encapsualtion of allegro functionality inside a number of classes, which are located in a library.

Certification of Authenticity:
I certify that this is entirely my own work, except where I have given
fully-documented references to the work of others. I understand the
definition and consequences of plagiarism and acknowledge that the assessor
of this assignment may, for the purpose of assessing this assignment:
- Reproduce this assignment and provide a copy to another member of
academic staff; and/or
- Communicate a copy of this assignment to a plagiarism checking
service (which may then retain a copy of this assignment on its
database for the purpose of future plagiarism checking)
*/


#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include "Game.h"



using namespace std;

int main()
{
	
	const double FPS_COUNT_60 = 16.7;

	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;


	 gpGame = new Game(FPS_COUNT_60);
	
	gpGame->initGame(600, 800, "Woods.png");

	gpGame->runGameLoop();
	
	gpGame->cleanupGame();

	delete gpGame;
	delete pPerformanceTracker;
	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");	
	return 0;
}