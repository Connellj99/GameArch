/*
Author: Conner Root
Class: EGP 310-01
Assignment: PA 2
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
	pGameObj = new Game();
	pGameObj->init(DISP_WIDTH, DISP_HEIGHT, TARGET_FRAMERATE);

	// Game Loop
	PerformanceTracker* pPerfomanceTracker = new PerformanceTracker();
	
	float sum = 0, cnt = 0;

	while (pGameObj->getExitState())
	{
		pPerfomanceTracker->clearTracker("loop");
		pPerfomanceTracker->startTracking("loop");

		pGameObj->gameLoop();

		pPerfomanceTracker->stopTracking("loop");
		cout << endl << "loop time: " << pPerfomanceTracker->getElapsedTime("loop");
		sum += pPerfomanceTracker->getElapsedTime("loop");
		cnt++;
	}

	cout << "\n\nAverage loop time: " << (sum / cnt) << endl 
		 << "Average Framrate: " << 1000/ (sum / cnt) << endl << endl;

	// Delete evrything
	delete pGameObj;
	delete pPerfomanceTracker;

	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");
	return 0;
}