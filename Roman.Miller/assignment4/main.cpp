/*
Miller Roman
EGP-310-01
Assigment 3
*/

#include <iostream>
#include <cassert>
#include <string>
#include <MemoryTracker.h>
#include <Vector2D.h>
#include "Game.h"

using namespace std;

int main()
{
	//Display info
	const Vector2D SCREEN_SIZE = Vector2D(800, 600);
	const float STARTING_FPS = 60;
		
	Game::initInstance();
	Game::getInstance()->init(SCREEN_SIZE, STARTING_FPS);
	Game::getInstance()->doLoop();
	Game::cleanupInstance();

	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");
	return 0;
}