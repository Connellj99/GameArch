/*
Author: Chun Tao Lin
Class: EGP-310-01
Assignment: Assignment 4
Certification of Authenticity: 
I certify that this assignment is entirely my own work.
I've built upon and added the code to have it work for assignment 4.
The work to get it working with this new assignment is my own work. 

Credits:
The basecode of assignment 3 belongs to Simon Steele.
Static instance implementation done by me, but heavily influenced by the shared contents in the lawson repo.
*/

// Non-standard library includes
#include <iostream>
#include <cassert>
#include <string>

// Dean-lib includes
#include <PerformanceTracker.h>
#include <MemoryTracker.h>

// Project-local includes
#include "Game.h"


using namespace std;

int main()
{
	//init the game instance
	Game::initInstance();

	//initialize the instance
	Game::getInstance()->init();

	// Execute game loop
	Game::getInstance()->DoLoop();

	// Destroy and cleanup display
	Game::getInstance()->cleanup();

	// Delete Game object
	Game::cleanupInstance();

	//Report any memory leaks.
	MemoryTracker::getInstance()->reportAllocations( cout );
	system("pause");
	return 0;
}