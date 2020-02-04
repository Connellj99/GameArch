/*Author: Cormac MacKinnon
Class: EGP-310-01
Assignment: pa 4
Certification of Authenticity: 
I certify that this assignment is entirely my own work.*/


#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include"Game.h"

using namespace std;

int main()
{
	Game::initInstance();
	Game::getInstance()->init();
	Game::getInstance()->doLoop();
	Game::getInstance()->cleanup();
	Game::cleanupInstance();

	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");

	return 0;

}