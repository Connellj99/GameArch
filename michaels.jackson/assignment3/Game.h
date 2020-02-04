
/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include "System.h"

class Game : public Trackable
{
public:
	System* mSystem;

	Game();
	~Game();
	void init(int = 600, int = 600);
	void cleanUp();

	void runGame(float fps = 60);

private:
	bool mInit = false;
	double mTimePerFrame;

};

extern Game* gpGame;