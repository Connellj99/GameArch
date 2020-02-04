/*
Author: Steven Pershyn
Class: EGP-310-01
Assignment: Assignment 2
Certification of Authenticity: I certify that this assignment is my own work, except where I referenced classmates' work and mentioned where relevant.
*/
#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include "Vector2D.h"

#include <GraphicsLib.h>
#include <GraphicsSystem.h>
#include <GraphicsBuffer.h>
#include <Color.h>

using namespace std;

int main()
{
	srand(time(NULL));
	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;
	const float CLOSE_TIME = 5.0;

	const string ASSET_PATH = "..\\..\\shared\\assets\\";
	const string BACKGROUND_FILENAME = "steps.png";
	const string SMURF_FILENAME = "smurf_sprites.png";
	const string FONT_FILENAME = "cour.ttf";
	const string TEXT = "Curse you Papa Smurf!";
	const string BACK_BUFFER_FILE = "backbuffer.jpg";
	const string RED_BUFFER_FILE = "redbuffer.jpg";
	const int FONT_SIZE = 30;
	const Color BLACK(0, 0, 0);
	const Color RED(255, 0, 0);
	const float SCALE = 0.33;
	const int SMURF_ROW_COUNT = 4;
	const int SMURF_COL_COUNT = 4;
	const int SMURF_WIDTH = 60;
	const int SMURF_HEIGHT = 60;
	const double SLEEP_TIME = 5.0;
	//calling init on a graphics system
	GraphicsSystem graphicsSystem = GraphicsSystem();
	graphicsSystem.Init(DISP_HEIGHT, DISP_WIDTH);

	//create 3 graphics buffers one steps, one smurfs, one red 800x600
	GraphicsBuffer *stepsBuffer = new GraphicsBuffer(ASSET_PATH + BACKGROUND_FILENAME);
	GraphicsBuffer *smurfsBuffer = new GraphicsBuffer(ASSET_PATH + SMURF_FILENAME);
	GraphicsBuffer *redBuffer = new GraphicsBuffer(DISP_WIDTH, DISP_HEIGHT, RED);

	//fill red buffer with "Curse you Papa Smurf!" in black using GraphicsSystem ->writeText function
	Font *fontType = new Font((ASSET_PATH + FONT_FILENAME), FONT_SIZE);
	graphicsSystem.writeText(redBuffer, 0, 0, fontType, BLACK, TEXT);
	//draw the red buffer then scale down the steps.png by 1/3
	int stepsX = (((redBuffer->getWidth()) - (stepsBuffer->getWidth() * SCALE)) / 2);
	int stepsY = (((redBuffer->getHeight()) - (stepsBuffer->getHeight() * SCALE)) / 2);
	graphicsSystem.draw(redBuffer, stepsX, stepsY, stepsBuffer, SCALE);
	//create 16 smurf sprites at random positions
	Sprite *smurfSprites[SMURF_COL_COUNT * SMURF_ROW_COUNT];
	for (int i = 0; i < SMURF_COL_COUNT; i++)
	{
		for (int j = 0; j < SMURF_ROW_COUNT; j++)
		{
			int randY = rand() % DISP_HEIGHT;
			int randX = rand() % DISP_WIDTH;

			smurfSprites[(i * (SMURF_COL_COUNT)) + j] = new Sprite((i * SMURF_WIDTH), (j * SMURF_HEIGHT), SMURF_WIDTH, SMURF_HEIGHT, smurfsBuffer);
			graphicsSystem.draw(redBuffer, randX, randY, smurfSprites[j + i], 1.0);
		}
	}
	graphicsSystem.draw(0, 0, redBuffer, 1.0);
	//save the backbuffer to a file using graphicssystem savebuffer
	graphicsSystem.saveBackBuffer(BACK_BUFFER_FILE);
	graphicsSystem.saveBuffer(redBuffer, RED_BUFFER_FILE);
	//save the red buffer to a file using save buffer function
	graphicsSystem.Flip();
	graphicsSystem.Rest(CLOSE_TIME);
	
	delete redBuffer;
	delete smurfsBuffer;
	delete stepsBuffer;
	delete fontType;
	for (int i = 0; i < SMURF_COL_COUNT * SMURF_ROW_COUNT; i++)
	{
		delete smurfSprites[i];
	}
	graphicsSystem.Cleanup();
	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");

	return 0;

}