/*
 * Adam Clarke
 * EGP-310-01
 * Midterm - Centipede
 * I certify that this assignment is entirely my own work.
*/
#include <MemoryTracker.h>
#include "Game.h"
#include "EventSystem.h"

int main()
{
	const auto CONFIG_FILEPATH = "..\\..\\clarke.adam\\midterm\\config.txt";

	EventSystem::initInstance();

	Game::initInstance();
	Game::getInstance()->init(CONFIG_FILEPATH);
	Game::getInstance()->doLoop();
	Game::getInstance()->cleanup();
	Game::cleanupInstance();

	EventSystem::cleanupInstance();

	MemoryTracker::getInstance()->reportAllocations(std::cout);
	system("pause");

	return 0;

}
