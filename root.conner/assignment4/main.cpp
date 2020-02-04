/*
Author: Conner Root
Class: EGP 310-01
Assignment: PA 4
Certification of Authenticity:
	I certify that this assignment is entirely my own work.
*/

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <stdlib.h>

#include "Game.h"

int main()
{
	// Constants
	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;
	const float TARGET_FRAMERATE = 60.0f;

	// Init Game object
	Game::initInstance();
	Game* pGame = Game::getInstance();
	pGame->init(DISP_WIDTH, DISP_HEIGHT, TARGET_FRAMERATE);

	// Game Loop
	pGame->gameLoop();

	// Delete
	pGame->cleanup();
	delete pGame;

	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");
	return 0;
}