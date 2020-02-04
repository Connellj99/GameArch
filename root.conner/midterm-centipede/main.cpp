/*
Author: Conner Root
Class: EGP 310-01
Assignment: Midterm - Centipede
Certification of Authenticity:
	I certify that this assignment is entirely my own work.
*/

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <stdlib.h>

#include "Game.h"
#include "EventSystem.h"

int main()
{
	// Start RNG
	srand(time(NULL));

	// Basic settings
	int dispWidth;
	int dispHeight;
	float targetFramrate;

	// Init Event System
	EventSystem::initInstance();

	// Init Game Object
	Game::initInstance();
	Game::getInstance()->init();

	// Game Loop
	Game::getInstance()->gameLoop();

	// Delete
	Game::cleanupInstance();
	EventSystem::getInstance()->cleanup();

	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");
	return 0;
}