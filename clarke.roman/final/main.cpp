/*
 * Adam Clarke
 * EGP-310-01
 * Assignment 5
 * I certify that this assignment is entirely my own work.
*/
#include <MemoryTracker.h>
#include "Game.h"
#include "EventSystem.h"

int main()
{
	const auto DISPLAY_DIMENSIONS = Vector2D(800, 600);
	const auto TARGET_FRAME_RATE = 60;

	EventSystem::initInstance();

	Game::initInstance();
	Game::getInstance()->init(DISPLAY_DIMENSIONS, TARGET_FRAME_RATE);
	Game::getInstance()->doLoop();
	Game::getInstance()->cleanup();
	Game::cleanupInstance();

	EventSystem::cleanupInstance();

	MemoryTracker::getInstance()->reportAllocations(std::cout);
	system("pause");

	return 0;

}
