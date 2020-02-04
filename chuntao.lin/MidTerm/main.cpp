/*
Author: Chun Tao Lin
Class: EGP-310-01
Assignment: Mid Term
Certification of Authenticity: 
I certify that this assignment is entirely my own work.
This assignment's base code is from assignment 5.
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
#include "EventSystem.h"

using namespace std;

int main()
{
	//Initial public game object of the event system
	EventSystem::initStaticEventSysInstance();

	// Initial public game objext of the game object
	Game::initStaticGameInstance();
	
	// Initialize the display
	Game::getStaticInstance()->init();

	// Execute game loop
	Game::getStaticInstance()->doLoop();

	// Destroy and cleanup display
	Game::getStaticInstance()->cleanup();

	// Delete Game object
	Game::destroyStaticGameInstance();

	//Delete Event system object
	EventSystem::destroyStaticEventSysInstance();

	//Report any memory Leaks
	MemoryTracker::getInstance()->reportAllocations( cout );
	system("pause");
	return 0;
}