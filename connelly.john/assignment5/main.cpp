/*
 * Adam Clarke
 * EGP-310-01
 * Assignment 3
 * I certify that this assignment is entirely my own work.
*/
#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include "Game.h"

int main()
{
	const std::string LOOP_TRACKER = "LOOP_TRACKER";
	auto pPerformanceTracker = new PerformanceTracker();

	const Vector2D DISPLAY_DIMENSIONS = Vector2D(800, 600);
	const auto TARGET_FRAME_RATE = 60;

	gpGame = new Game();
	gpGame->init(DISPLAY_DIMENSIONS, TARGET_FRAME_RATE);

	while (!gpGame->getShouldExit())
	{
		pPerformanceTracker->clearTracker(LOOP_TRACKER);
		pPerformanceTracker->startTracking(LOOP_TRACKER);

		gpGame->doLoop();

		pPerformanceTracker->stopTracking(LOOP_TRACKER);
		std::cout << "loop time: " << pPerformanceTracker->getElapsedTime(LOOP_TRACKER) << " ms" << std::endl;
	}

	gpGame->cleanup();
	delete gpGame;

	delete pPerformanceTracker;

	MemoryTracker::getInstance()->reportAllocations(std::cout);
	system("pause"); 

	return 0;

}
