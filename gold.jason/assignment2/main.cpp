/*
Author: Jason  Gold
Class: EGP 310-01
Assignment: Assignment 2
Certification of Authenticity:
	I certify that this assignment is entirely my own work.

References:
Nick Dacosta
Chun Tao Lin
Conner Root
Piazza
Andrew Tiller
*/

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <GraphicsSystem.h>
#include <iostream>

using namespace std;

int main()
{
	//variables
	int fontSize = 32;
	int fontPosX = 0;
	int fontPosY = 0;
	int width = 800;
	int height = 600;
	double sleepTime = 5.0;
	float scale = 1.0f;
	Color red = Color(255, 0, 0);
	Color black = Color(0, 0, 0);
	string assetPath = "..\\..\\shared\\assets\\";
	string backgroundImage = "steps.png";
	string smurfImage = "smurf_sprites.png";
	string text = "Curse you Papa Smurf!";
	string fontFileName = "cour.ttf";
	GraphicsSystem* graphSystem = new GraphicsSystem();

	//initialize GraphicsSystem
	graphSystem->initGraphicsSystem(width, height);

	//create graphics buffers
	GraphicsBuffer* image = new GraphicsBuffer(assetPath + backgroundImage);
	GraphicsBuffer* smurfs = new GraphicsBuffer(assetPath + smurfImage);
	GraphicsBuffer* background = new GraphicsBuffer(width, height, red);

	//write text to screen
	Font textFont = Font(assetPath + fontFileName, fontSize);
	graphSystem->writeText(fontPosX, fontPosY, textFont, black, text);

	//create sprites
	Sprite bg = Sprite(image, 200, 150, 1600, 1200);
	Sprite smurf = Sprite(smurfs, 0, 0, 800, 600);
	Sprite bg2 = Sprite(background, 0, 0, 800, 600);

	//add sprites to the display
	graphSystem->draw(bg2.getLocX(), bg2.getLocY(), bg2, 1.0f);
	graphSystem->draw(bg.getLocX(), bg.getLocY(), bg, 0.3f);
	graphSystem->draw(smurf.getLocX(), smurf.getLocY(), smurf, 1.0f);

	// Flip display
	graphSystem->flipDisplay();

	//tell the screen to rest
	al_rest(sleepTime);

	// Delete everything
	delete graphSystem;

	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");
}