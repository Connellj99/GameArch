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
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	Game::initInstance();
	Game* game = Game::getInstance();

	game->init(WINDOW_WIDTH, WINDOW_HEIGHT);



	game->runGame();



	game->cleanUp();

	Game::cleanupInstance();



	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");

	return 0;

}