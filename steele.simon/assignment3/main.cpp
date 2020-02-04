/*
Author: Simon Steele
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity: I certify that this
assignment is entirely my own work.
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

extern Game * gpGameObject;

int main()
{
	// Initial public game objext
	gpGameObject = new Game();

	// Initialize the display
	gpGameObject->init();

	// Execute game loop
	gpGameObject->DoLoop();

	// Destroy and cleanup display
	gpGameObject->cleanup();

	// Delete Game object
	delete gpGameObject;

	MemoryTracker::getInstance()->reportAllocations( cout );
	system("pause");
	return 0;
}