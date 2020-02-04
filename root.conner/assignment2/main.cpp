/*
Author: Conner Root
Class: EGP 310-01
Assignment: PA 2
Certification of Authenticity:
	I certify that this assignment is entirely my own work.
*/

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <stdlib.h>

#include "GraphicsSystem.h"

using namespace std;

int main()
{
	// Constants
	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;
	const int FONT_SIZE = 24;
	const int FONT_X_POS = 0;
	const int FONT_Y_POS = 0;
	const int NUM_SMURFS = 16;

	const string ASSET_PATH = "..\\..\\shared\\assets\\";
	const string BACKGROUND_FILENAME = "steps.png";
	const string SMURFS_FILENAME = "smurf_sprites.png";
	const string TEXT_STRING = "Curse you Papa Smurf!";
	const string FONT_FILENAME = "cour.ttf";

	const float NEW_SCALE = 0.333f;

	
	const double SLEEP_TIME_IN_SECONDS = 5.0;

	// Init rand generator
	srand(time(NULL));

	// Graphics System
	GraphicsSystem graphSystem = GraphicsSystem();
	// Init Graphics System
	graphSystem.initGraphicsSystem(DISP_WIDTH, DISP_HEIGHT);

	// Create Colors
	Color red = Color(255, 0, 0);
	Color black = Color(0, 0, 0);

	// Create Buffers
	GraphicsBuffer* pStepsBuffer = new GraphicsBuffer(ASSET_PATH + BACKGROUND_FILENAME); // Steps picture
	GraphicsBuffer* pSmurfBuffer = new GraphicsBuffer(ASSET_PATH + SMURFS_FILENAME); // Smurfs
	GraphicsBuffer* pBackground = new GraphicsBuffer(DISP_WIDTH, DISP_HEIGHT, red); // Red background

	// Create Sprites
	int stepsXPos = ((pBackground->getWidth() - (pStepsBuffer->getWidth() * NEW_SCALE)) / 2.0f);
	int stepsYPos = ((pBackground->getHeight() - (pStepsBuffer->getHeight() * NEW_SCALE)) / 2.0f);
	Sprite* pStepsSprite = new Sprite(pStepsBuffer, stepsXPos, stepsYPos, pStepsBuffer->getWidth(), pStepsBuffer->getHeight());
	Sprite* pRedSprite = new Sprite(pBackground, 0, 0, pBackground->getWidth(), pBackground->getHeight());
	Sprite* pSmurfs[NUM_SMURFS];

	// Create Font
	Font* pFont = new Font((ASSET_PATH + FONT_FILENAME), FONT_SIZE);

	// Write Text
	graphSystem.writeText(0, 0, pFont, black, TEXT_STRING);

	// Draw Sprites
	graphSystem.draw(pRedSprite->getXPos(), pRedSprite->getYPos(), pRedSprite, 1.0);
	graphSystem.draw(pStepsSprite->getXPos(), pStepsSprite->getYPos(), pStepsSprite, NEW_SCALE);

	int smurfWidth = pSmurfBuffer->getWidth() / 4;
	int smurfHeight = pSmurfBuffer->getHeight() / 4;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int smurfXPos = rand() % DISP_WIDTH;
			int smurfYPos = rand() % DISP_HEIGHT;
			int index = (i * 4) + j;

			pSmurfs[index] = new Sprite(pSmurfBuffer, j*smurfWidth, i*smurfHeight, smurfWidth, smurfHeight);

			graphSystem.draw(smurfXPos, smurfYPos, pSmurfs[index], 1.0);
		}
	}

	// Flip display
	graphSystem.flipDisplay();
	graphSystem.wait(SLEEP_TIME_IN_SECONDS);

	// Delete buffers
	delete pStepsBuffer;
	delete pSmurfBuffer;
	delete pBackground;
	// Delete font
	delete pFont;
	// Delete sprites
	delete pStepsSprite;
	delete pRedSprite;
	for (int a = 0; a < NUM_SMURFS; a++)
		delete pSmurfs[a];
	// Delete graphics system
	graphSystem.cleanup();

	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");
	return 0;
}