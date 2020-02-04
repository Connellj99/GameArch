/*
Author: Dianna  Cornett
This assignment was completed using Amelia Payne's Assignment 4 as a base.
*/

#include <iostream>
#include <cassert>
#include <string>

#include "Game.h"
#include <PerformanceTracker.h>
#include <MemoryTracker.h>


//Define constants 
extern const double SPEED_CHANGE_AMOUNT = .01;
extern const int DISP_WIDTH = 800;
extern const int DISP_HEIGHT = 600;
extern const std::string ASSET_PATH = "..\\..\\shared\\assets\\";
extern const std::string SMURF_FILENAME = "smurf_sprites.png";
extern const std::string DEAN_SMURF_FILENAME = "dean_sprites.png";
extern const std::string WOODS_FILENAME = "Woods.png";

extern const float TIME_PER_SPRITE = .1;

extern const int SMURF_SHEET_COLS = 4;
extern const int SMURF_SHEET_HIEGHT = 4;

int main()
{
	//Create the game
	Game::initInstance();

	//Init the game 
	Game::getInstance()->init();

	//Start the game loop
	Game::getInstance()->doLoop();

	//Clean up data
	Game::getInstance()->cleanup();

	//Clean up the instance
	Game::cleanupInstance();

	//Report memory allocations
	MemoryTracker::getInstance()->reportAllocations(std::cout);

	//Wait and exit
	system("pause");
	return 0;

}

