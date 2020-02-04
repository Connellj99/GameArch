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
	const int GAME_WIDTH = 800;
	const int GAME_HEIGHT = 600;
	const int GAME_FPS = 60;

	//Start of game

	EventSystem::createInstance();
	EventSystem* eventListener = EventSystem::getInstance();

	InputTranslator* translator = new InputTranslator(eventListener);

	Game::createInstance(eventListener, GAME_WIDTH, GAME_HEIGHT, GAME_FPS);
	Game* smurfGame = Game::getInstance();

	smurfGame->init();

	smurfGame->doLoop();

	delete translator;
	Game::cleanupInstance();
	smurfGame->cleanup();
	EventSystem::cleanupInstance();
	eventListener->cleanup();

	//End of game

	cout << endl;
	MemoryTracker::getInstance()->reportAllocations(cout);


	system("pause");

	return 0;

}