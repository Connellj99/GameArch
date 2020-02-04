/*
Author: Steven Pershyn
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is my own work, except where I referenced classmates' work and mentioned where relevant.
*/
#pragma once
#include "System.h"
class Game : public Trackable
{
public:
	

	Game();
	~Game();
	void init(int = 600, int = 600);
	void cleanUp();

	void runGame(float fps = 60);
	System* mSystem;

private:
	bool mInit;
	double mTimePerFrame;
	Sprite* woodsSprite;
	

};

extern Game* gpGame;