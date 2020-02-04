/*
Author: David Bakaleinik & Grady Mayo
Class: EGP-310
Assignment: Final Project
Date Assigned: 04/03/2019 - 12:30pm
Due Date: 03/04/2019 - 12:01pm

Description:
A re-creation of the classic Milipede game

Certification of Authenticity:
I certify that this is entirely my own work, except where I have given
fully-documented references to the work of others. I understand the
definition and consequences of plagiarism and acknowledge that the assessor
of this assignment may, for the purpose of assessing this assignment:
- Reproduce this assignment and provide a copy to another member of
academic staff; and/or
- Communicate a copy of this assignment to a plagiarism checking
service (which may then retain a copy of this assignment on its
database for the purpose of future plagiarism checking)
*/

#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include "Game.h"
#include "EventSystem.h"
#include "FileReader.h"
#include "InputTranslator.h"

const std::string GAME_ASSETS = "..\\GameAssets\\";


void main()
{
	double fps = 1000 / 16.7;

	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;
	EventSystem::initSystem();
	EventSystem* pEventSystem = EventSystem::getInstance();
	Game::initInstance(fps, pEventSystem);
	Game* pGame = Game::getInstance();
	InputTranslator* pTranslator = new InputTranslator(pEventSystem);
	//double fps = 1000 / reader->getFPS();
	
	FileReader::initReader("AssetInfo.txt", GAME_ASSETS);
	FileReader* reader = FileReader::getInstance();

	pGame->initGame(600, 900, pEventSystem);

	pGame->runGameLoop();

	pGame->cleanupGame();

	Game::deleteInstance();

	reader->deleteReader();

	//delete pTranslator;
	EventSystem::deleteInstance();
	delete pPerformanceTracker;
	MemoryTracker::getInstance()->reportAllocations(std::cout);
	system("Pause");
}