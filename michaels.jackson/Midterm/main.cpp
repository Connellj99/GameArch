/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/


#include "Game.h"

int main()
{
	const int WINDOW_WIDTH = 600;
	const int WINDOW_HEIGHT = 600;
	EventSystem::initInstance();
	EventSystem * eventSys = EventSystem::getInstance();
	
	cout << "Event: " << eventSys << endl;

	Game::initInstance(eventSys, 15);
	Game* game = Game::getInstance();
	InputTranslator translator(eventSys);
	translator.init();


	game->init(WINDOW_WIDTH, WINDOW_HEIGHT);



	game->runGame();



	game->cleanUp();

	EventSystem::cleanupInstance();

	Game::cleanupInstance();



	MemoryTracker::getInstance()->reportAllocations(cout);
	
	system("pause");

	return 0;

}