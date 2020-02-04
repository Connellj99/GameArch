#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <GraphicsSystem.h>
#include <GraphicsBuffer.h>
#include <Sprite.h>
#include "Game.h"

using namespace std;

int main()
{
	
	//Start of code
	Game::mpGameInstance = new Game(800, 600, 60);
	const string WOODS_FILENAME = "woods.png";
	const string WOODS_BUFFER_NAME = "woods";

	const int SPRITE_SIZE = 60;

	const string SMURFS_UNIT_NAME = "theSmurf";

	const string SMURFS_FILENAME = "smurf_sprites.png";
	const string SMURFS_BUFFER_NAME = "smurfs";

	const string DEAN_FILENAME = "dean_sprites.png";
	const string DEAN_BUFFER_NAME = "deans";


	Game::mpGameInstance->init();
	Game::mpGameInstance->createBuffer(WOODS_BUFFER_NAME, WOODS_FILENAME, 800, 600);
	Game::mpGameInstance->drawBackground(WOODS_BUFFER_NAME, 0, 0);
	
	Game::mpGameInstance->createAnimation(SMURFS_BUFFER_NAME, SMURFS_FILENAME, SPRITE_SIZE);
	Game::mpGameInstance->createAnimation(DEAN_BUFFER_NAME, DEAN_FILENAME, SPRITE_SIZE);
	
	Game::mpGameInstance->createUnit(SMURFS_UNIT_NAME);

	Game::mpGameInstance->addAnimationToUnit(SMURFS_UNIT_NAME, SMURFS_BUFFER_NAME);
	Game::mpGameInstance->addAnimationToUnit(SMURFS_UNIT_NAME, DEAN_BUFFER_NAME);

	Game::mpGameInstance->swapOnEnter(SMURFS_UNIT_NAME);
	Game::mpGameInstance->createOnMouseDown(SMURFS_UNIT_NAME);

	Game::mpGameInstance->doLoop();

	Game::mpGameInstance->cleanup();

	//End of game

	cout << endl;
	MemoryTracker::getInstance()->reportAllocations(cout);


	system("pause");

	return 0;

}