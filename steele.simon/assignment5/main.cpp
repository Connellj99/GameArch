/*
Author: Simon Steele
Class: EGP-310-01
Assignment: Assignment 5
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

// Graphics-lib includes
#include <EventSystem.h>

// Project-local includes
#include "Game.h"


using namespace std;

int main()
{
	// Initialize static event system
	EventSystem::initStaticInstance();

	// Initial public game objext
	Game::initStaticInstance();

	// Initialize the display
	Game::getStaticInstance()->init();

	// Execute game loop
	Game::getStaticInstance()->doLoop();

	// Destroy and cleanup display
	Game::getStaticInstance()->cleanup();

	// Delete Game object
	Game::destroyStaticInstance();

	// Delete the static event system
	EventSystem::destroyStaticInstance();

	MemoryTracker::getInstance()->reportAllocations( cout );
	system("pause");
	return 0;
}