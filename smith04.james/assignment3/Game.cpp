#include "Game.h"
#include "GraphicsLib/InputManager.h"

Game::Game(float w, float h, float t)
{
	init(w, h, t);
}

Game::~Game()
{
	cleanup();
}

void Game::init(float w, float h, float t)
{
	pPerformanceTracker->startTracking(INIT_TRACKER_NAME);

	timeScale = t;

	mpGameSys = new System(w, h);
	woodsBuffer = new GraphicsBuffer(WOODS_PATH.c_str());
	smurfBuffer = new GraphicsBuffer(SMURF_PATH.c_str());
	deanBuffer = new GraphicsBuffer(DEAN_PATH.c_str());

	smurfUnit = new Unit();
	smurfUnit->setX(350.0);
	smurfUnit->setY(250.0);
	smurfUnit->loadAnimation(smurfBuffer, 4, 4);

	mpInputManager = new InputManager();

	pPerformanceTracker->stopTracking(INIT_TRACKER_NAME);

	

}

void Game::cleanup()
{
	delete pPerformanceTracker;
	delete timer;
	delete mpGameSys;
	delete woodsBuffer;
	delete smurfBuffer;
	delete deanBuffer;

	delete smurfUnit;
	delete mpInputManager;
}

void Game::gameLoop()
{
	do {
		pPerformanceTracker->clearTracker("loop");
		pPerformanceTracker->startTracking("loop");

		timer->start();

		getInput();
		update();
		render();

		timer->sleepUntilElapsed(timeScale);
		timer->stop();

		pPerformanceTracker->stopTracking("loop");
		std::cout << std::endl << "Time to loop: " << pPerformanceTracker->getElapsedTime("loop");
	} 
	while (!exit);
}

void Game::getInput()
{
	//get input from allegro
	mpInputManager->checkInput();
}

void Game::update()
{
	smurfUnit->update();
}

void Game::render()
{
	woodsBuffer->draw(0, 0);

	smurfUnit->draw();

	mpGameSys->flip();
}

void Game::shouldExit()
{
	exit = true;
}

void Game::adjustTime(float change)
{
	timeScale *= change;
}

//Switches smurf between normal smurf and Dean smurf
void Game::switchAnim()
{
	if (isDean)
	{
		smurfUnit->loadAnimation(smurfBuffer, 4, 4);
	}
	else
	{
		smurfUnit->loadAnimation(deanBuffer, 4, 4);
	}

	isDean = !isDean;
}