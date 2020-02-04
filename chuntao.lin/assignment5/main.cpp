/*
Author: Chun Tao Lin
Class: EGP-310-01
Assignment: Assignment 5
Certification of Authenticity: 
I certify that this assignment is entirely my own work.

I recieved the permission to use the starting code from assignment 4 from Simon Steele.
I've added to it to fit requirements of assignment 5. While also editing the past
work from assignment 4 that was given.
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