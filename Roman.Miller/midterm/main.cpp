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
#include "EventSystem.h"

using namespace std;

int main()
{
	EventSystem::initInstance();
	//Display info
	const Vector2D SCREEN_SIZE = Vector2D(800, 800);
	const float STARTING_FPS = 60;
		
	Game::initInstance();
	Game::getInstance()->init(SCREEN_SIZE, STARTING_FPS);
	Game::getInstance()->doLoop();
	Game::cleanupInstance();


	EventSystem::cleanupInstance();
	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");
	return 0;
}