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
	Game* smurfWalk = new Game(800, 600, 60);
	const string WOODS_FILENAME = "woods.png";
	const string WOODS_BUFFER_NAME = "woods";

	const int SPRITE_SIZE = 60;

	const string SMURFS_UNIT_NAME = "theSmurf";

	const string SMURFS_FILENAME = "smurf_sprites.png";
	const string SMURFS_BUFFER_NAME = "smurfs";

	const string DEAN_FILENAME = "dean_sprites.png";
	const string DEAN_BUFFER_NAME = "deans";


	smurfWalk->init();
	smurfWalk->createBuffer(WOODS_BUFFER_NAME, WOODS_FILENAME, 800, 600);
	smurfWalk->drawBackground(WOODS_BUFFER_NAME, 0, 0);
	
	smurfWalk->createAnimation(SMURFS_BUFFER_NAME, SMURFS_FILENAME, SPRITE_SIZE);
	smurfWalk->createAnimation(DEAN_BUFFER_NAME, DEAN_FILENAME, SPRITE_SIZE);
	
	smurfWalk->createUnit(SMURFS_UNIT_NAME);

	smurfWalk->addAnimationToUnit(SMURFS_UNIT_NAME, SMURFS_BUFFER_NAME);
	smurfWalk->addAnimationToUnit(SMURFS_UNIT_NAME, DEAN_BUFFER_NAME);

	smurfWalk->swapOnEnter(SMURFS_UNIT_NAME);
	smurfWalk->drawUnitAtMouse(SMURFS_UNIT_NAME);

	smurfWalk->doLoop();

	smurfWalk->cleanup();

	//End of game

	delete smurfWalk;
	cout << endl;
	MemoryTracker::getInstance()->reportAllocations(cout);


	system("pause");

	return 0;

}