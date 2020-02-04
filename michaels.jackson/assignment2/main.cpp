/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#include <iostream>
#include <cassert>
#include <string>
#include <random>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <GraphicsLib.h>

using namespace std;

int main()
{
	Sprite* smurfs[16];

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	GraphicsSystem window (WINDOW_WIDTH, WINDOW_HEIGHT);
	window.init();

	Font cour("cour.ttf", 24);


	GraphicsBuffer stepBuffer("steps.png");
	Sprite stepSprite(&stepBuffer, 0, 0);

	GraphicsBuffer redSquare(WINDOW_WIDTH, WINDOW_HEIGHT);
	redSquare.setColor(RED);
	Sprite redSprite(&redSquare, 0, 0);

	GraphicsBuffer smurfBuffer("smurf_sprites.png");


	window.writeText("Curse you Papa Smurf!", &redSquare, 50, 50, &cour, BLACK);


	window.draw(&redSprite, 0, 0, 1);


	window.draw(&stepSprite, 140, 90, 1.0/3.0);

	int x, y, size = 60;
	for (int i = 0; i < 16; i++) {
		x = (i % 4) * size;
		y = (i / 4) * size;

		smurfs[i] = new Sprite(&smurfBuffer, x, y, size, size);
		

		window.draw( smurfs[i], rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT, 1);
	}

	for (int i = 0; i < 16; i++) {
		delete smurfs[i];
	}

	window.flip();
	
	window.saveBuffer("backbuffer.jpg");
	
	window.saveBuffer("redbuffer.jpg", &redSquare);

	MemoryTracker::getInstance()->reportAllocations(cout);

	al_rest(5.0);


	return 0;

}