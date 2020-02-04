/*
Author: Chun Tao Lin
Class: EGP-310-01
Assignment: Assignment 3

Certification of Authenticity: I certify that this assignment is entirely my own work.
All this code was written by myself.

Notes:
 I finally managed to believe finish all of this assignment. Thanks for pushing us to finish even if it was late
*/
#ifndef main_h

#define main_h
#include "Colors.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Font.h"
#include "Sprites.h"
#include "Game.h"

#endif
int main()
{
	//consts that contain any and all asset paths in the shared folder
	const std::string ASSET_PATH = "..\\..\\shared\\assets\\";
	const std::string STEPS_FILENAME = "steps.png";
	const std::string DEAN_FILENAME = "dean_sprites.png";
	const std::string SMURF_FILENAME = "smurf_sprites.png";
	const std::string WOODS_FILENAME = "Woods.png";
	const std::string FONT_FILENAME = "cour.ttf";
	const int FONT_SIZE = 24;

	//create new game object that will initialize the systems
	gGameObj = new Game();

	//start drawing the initial images. so the background and sprite in the center
	gGameObj->drawStartingData((ASSET_PATH + WOODS_FILENAME), (ASSET_PATH + SMURF_FILENAME), (ASSET_PATH + DEAN_FILENAME));

	//run through the game loop.
	gGameObj->gameLoop();

	delete gGameObj;
	gGameObj = NULL;

	
	//report any memory that hasn't been cleared
	MemoryTracker::getInstance()->reportAllocations(std::cout);
	system("pause");
	return 0;
}