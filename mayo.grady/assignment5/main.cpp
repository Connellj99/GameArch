/*
Author: Grady Mayo 
Class: EGP-310 <Section 01>
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <GraphicsLib.h>
#include "Game.h"
#include "EventSystem.h"

using namespace std;

int main()
{
	//set up event system
	EventSystem::initInstance();

	//create instance
	Game::initInstance();

	//initialize, do loop, cleanup
	Game::getInstance()->init();
	Game::getInstance()->doLoop();
	Game::getInstance()->cleanup();

	//delete instance
	Game::cleanupInstance();

	//cleanup event system
	EventSystem::cleanupInstance();

	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");

	return 0;

}