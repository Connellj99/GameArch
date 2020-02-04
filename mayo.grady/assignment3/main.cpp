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

using namespace std;

extern Game * gpGame;

int main()
{
	//create and init game object
	gpGame = new Game();
	gpGame->init();
	gpGame->doLoop();
	gpGame->cleanup();

	delete gpGame;

	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");

	return 0;

}