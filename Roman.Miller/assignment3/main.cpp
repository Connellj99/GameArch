/*
Miller Roman
EGP-310-01
Assigment 3
*/

#include <iostream>
#include <cassert>
#include <string>
#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <Vector2D.h>
#include "Game.h"

using namespace std;

Game * gpGameObject;

int main()
{
	//Display info
	const Vector2D SCREEN_SIZE = Vector2D(800, 600);
	const float STARTING_FPS = 60;

	//Memory Tracker
	const string TRACKER = "Loop_Time";
	//------------------------------------------------------------------------------
	{
		PerformanceTracker tracker = PerformanceTracker();
		gpGameObject = new Game();
		gpGameObject->init(SCREEN_SIZE, STARTING_FPS);

		while (gpGameObject->checkIfStillLoop())
		{
			tracker.clearTracker(TRACKER);
			tracker.startTracking(TRACKER);

			gpGameObject->doLoop();

			tracker.stopTracking(TRACKER);
			cout << tracker.getElapsedTime(TRACKER) << endl;
		}

		gpGameObject->cleanup();
		delete gpGameObject;
	}
		MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");
	return 0;
}