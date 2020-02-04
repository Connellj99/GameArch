/*Author: Cormac MacKinnon
Class: EGP-310-01
Assignment: pa 5
Certification of Authenticity: 
I certify that this assignment is entirely my own work.*/


#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include "Game.h"
#include "EventSystem.h"

using namespace std;

int main()
{
	EventSystem::initInstance();

	Game::initInstance();
	Game::getInstance()->init();
	Game::getInstance()->doLoop();
	Game::getInstance()->cleanup();
	Game::cleanupInstance();

	EventSystem::cleanupInstance();

	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");

	return 0;

}