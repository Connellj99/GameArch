#include "Game.h"

Game::Game()
{
	return;
}

void Game::init()
{
	mSys->initSys();
	mpTimer = new Timer;
}

void Game::doLoop()
{
	mpTimer->start();
	PerformanceTracker* tracker = new PerformanceTracker();
	tracker->startTracking("draw");

	do 
	{
		mpTimer->start();
		tracker->clearTracker("draw");
		tracker->startTracking("draw");


		//get user input and adjust game state
		input();

		//draw current game state
		draw();

		//update game state
		update();

		mpTimer->sleepUntilElapsed(16.7);
		tracker->stopTracking("draw");

		cout << tracker->getElapsedTime("draw") << endl;
	} while (!escape);

	delete tracker;
	tracker = nullptr;
}

void Game::update()
{
	return;
}

void Game::input()
{
	mSys->getKeyState();
	mSys->getMouseState();
}

void Game::draw() 
{

}

void Game::draw(GraphicsBuffer* buff)
{
	mSys->draw(buff);
	return;
}

Game::~Game()
{
	mSys->~System();
}
