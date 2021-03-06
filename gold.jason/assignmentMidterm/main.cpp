#include <iostream>
#include <vector>
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Color.h"
#include "Font.h"
#include "Sprites.h"
#include "Game.h"
#include "System.h"
#include "Snake.h"

#include<PerformanceTracker.h>
#include<MemoryTracker.h>
#include<time.h>

int main()
{
	EventSystem::initInstance();
	EventSystem* eventSys = EventSystem::getEventSys();

	Game::initInstance(eventSys);
	Game* pGame = Game::getInstance(); 

	pGame->initGame(DISP_HEIGHT, DISP_WIDTH);

	pGame->getSystem()->getGraphicsSystem()->flip_Display();

	pGame->doLoop();
	
	pGame->cleanUpInstance();

	MemoryTracker::getInstance()->reportAllocations(std::cout);
	system("pause");
	return 0;

}                                                                                                                                                                                                                                                                     