/*Author: Cormac MacKinnon
Class: EGP-310-01
Assignment: pa 2 
Certification of Authenticity: 
I certify that this assignment is entirely my own work.*/


#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <GraphicsLib.h>
#include "GraphicsSystem.h"


using namespace std;

int main()
{
	srand(time(NULL));

	//constants
	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;
	const string ASSET_PATH = "..\\..\\shared\\assets\\";
	const string STEPS_IMAGE = "steps.png";
	const string SMURFS_IMAGE = "smurf_sprites.png";
	const string FONT_NAME = "cour.ttf";
	const string TEXT = "Curse you Papa Smurf!";
	const string BACK_BUFFER_FILE = "backbuffer.jpg";
	const string RED_BUFFER_FILE = "redbuffer.jpg";
	const int RED_R_VALUE = 255;
	const int RED_G_VALUE = 0;
	const int RED_B_VALUE = 0;
	const int BLACK_R_VALUE = 0;
	const int BLACK_G_VALUE = 0;
	const int BLACK_B_VALUE = 0;
	const float SCALE_FACTOR = 0.333;
	const float SCALE_FACTOR_DEFAULT = 1.0;
	const int SMURF_HEIGHT_IMAGE = 4;
	const int SMURF_COLS = 4;
	const double SLEEP_TIME = 5.0;

	GraphicsSystem graphicsSystem;

	//initialize the graphics system and create display
	graphicsSystem.init(DISP_WIDTH, DISP_HEIGHT);

	//created colors
	Color redColor(RED_R_VALUE, RED_G_VALUE, RED_B_VALUE);
	Color blackColor(BLACK_R_VALUE, BLACK_G_VALUE, BLACK_B_VALUE);

	//creation of font
	Font *pFontType = new Font((ASSET_PATH + FONT_NAME), 32);

	//creation of three graphics buffers
	GraphicsBuffer *pStepsBuffer = new GraphicsBuffer(ASSET_PATH + STEPS_IMAGE);
	GraphicsBuffer *pSmurfsBuffer = new GraphicsBuffer(ASSET_PATH + SMURFS_IMAGE);
	GraphicsBuffer *pRedBuffer = new GraphicsBuffer(DISP_WIDTH, DISP_HEIGHT, redColor);

	//more constants
	const int SMURF_HEIGHT = pSmurfsBuffer->getHeight() / SMURF_HEIGHT_IMAGE;
	const int SMURF_WIDTH = pSmurfsBuffer->getWidth() / SMURF_COLS;

	//smurf sprite array initializing
	Sprite * pSmurfSprites[SMURF_COLS * SMURF_HEIGHT_IMAGE];

	//determine position of steps image
	int stepsXPos = ((pRedBuffer->getWidth() - (pStepsBuffer->getWidth() * SCALE_FACTOR)) / 2.0);
	int stepsYPos = ((pRedBuffer->getHeight() - (pStepsBuffer->getHeight() * SCALE_FACTOR)) / 2.0);

	//draw text onto red buffer
	graphicsSystem.writeText(pRedBuffer, 0.0, 0.0, pFontType, blackColor, TEXT);

	//draw steps onto red buffer in center
	graphicsSystem.draw(pRedBuffer, stepsXPos, stepsYPos, pStepsBuffer, SCALE_FACTOR);

	//separates and draws the individual sprites on buffer in random locations
	for (int i = 0; i < SMURF_COLS; i++)
	{
		for (int k = 0; k < SMURF_HEIGHT_IMAGE; k++)
		{
			int randY = rand() % DISP_HEIGHT;
			int randX = rand() % DISP_WIDTH;

			pSmurfSprites[(i * (SMURF_COLS)) + k] = new Sprite((i * SMURF_WIDTH), (k * SMURF_HEIGHT), SMURF_WIDTH, SMURF_HEIGHT, pSmurfsBuffer);

			graphicsSystem.draw(pRedBuffer, randX, randY, pSmurfSprites[k + i], SCALE_FACTOR_DEFAULT);
		}
	}

	//draw red buffer
	graphicsSystem.draw(0.0f, 0.0f, pRedBuffer, SCALE_FACTOR_DEFAULT);

	//save various buffers accordingly
	graphicsSystem.saveBackBuffer(BACK_BUFFER_FILE);
	graphicsSystem.saveBuffer(pRedBuffer, RED_BUFFER_FILE);
	//flip display
	graphicsSystem.flipDisplay();
	//close program after 5 seconds
	graphicsSystem.rest(SLEEP_TIME);
	//start cleanup
	graphicsSystem.cleanup();
	//delete created pointers to prevent memory leaks
	delete pRedBuffer;
	delete pSmurfsBuffer;
	delete pStepsBuffer;
	delete pFontType;
	for (int i = 0; i < SMURF_HEIGHT_IMAGE * SMURF_COLS; i++) 
	{
		delete pSmurfSprites[i];
	}


	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");

	return 0;

}