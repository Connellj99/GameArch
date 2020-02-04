/*
Author: Grady Mayo 
Class: EGP-310 <Section 01>
Assignment: Assignment 2 
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/
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
	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;
	const float HALF = 2.0f;
	const string ASSET_PATH = "..\\..\\shared\\assets\\";
	const string STEPS_FILENAME = "steps.png";
	const string SMURFS_FILENAME = "smurf_sprites.png";
	const string CURSE_TEXT = "Curse you Papa Smurf!";
	const float SCALE_FACTOR = 0.33f;
	const float NORM_SCALE = 1.0f;
	const int FULL_COLOR = 255;
	const int NO_COLOR = 0;
	const string FONT_FILENAME = "cour.ttf";
	const int FONT_SIZE = 24;
	const double SLEEP_TIME_IN_SECONDS = 5.0;
	const int NUM_SMURFS = 16;
	const int SMURF_COLS_ROWS = 4;
	const string BACK_FILENAME = "backbuffer.jpg";
	const string COLOR_FILENAME = "colorbuffer.jpg";

	srand(time(NULL));

	//create graphics system object at set height and width
	GraphicsSystem gObject;
	gObject.init(DISP_WIDTH, DISP_HEIGHT);

	//create graphic buffers for steps and smurfs
	GraphicsBuffer * pStepsBuffer = new GraphicsBuffer( ASSET_PATH + STEPS_FILENAME );
	GraphicsBuffer * pSmurfBuffer = new GraphicsBuffer( ASSET_PATH + SMURFS_FILENAME );

	//create red color object and pass into new color buffer
	Color redColor( FULL_COLOR, NO_COLOR, NO_COLOR );
	GraphicsBuffer * pColorBuffer = new GraphicsBuffer( DISP_WIDTH, DISP_HEIGHT, redColor );

	//create black color and font for text and write text to buffer
	Color blackColor( NO_COLOR, NO_COLOR, NO_COLOR );
	Font * textFont = new Font( FONT_SIZE, ( ASSET_PATH + FONT_FILENAME ) );
	gObject.writeText( pColorBuffer, 0, 0, textFont, blackColor, CURSE_TEXT );

	//find location for steps
	int stepsX = ( ( pColorBuffer->getBitmapWidth() - ( pStepsBuffer->getBitmapWidth() * SCALE_FACTOR ) ) / HALF );
	int stepsY = ( ( pColorBuffer->getBitmapHeight() - ( pStepsBuffer->getBitmapHeight() * SCALE_FACTOR ) ) / HALF );

	gObject.draw(pStepsBuffer, stepsX, stepsY, SCALE_FACTOR, pColorBuffer);

	//array for smurfs
	Sprite * paSmurfs[NUM_SMURFS];

	int smurfX = pSmurfBuffer->getBitmapWidth() / SMURF_COLS_ROWS;
	int smurfY = pSmurfBuffer->getBitmapHeight() / SMURF_COLS_ROWS;

	//create smurf sprites
	for (int i = 0; i < SMURF_COLS_ROWS; i++)
	{
		for (int j = 0; j < SMURF_COLS_ROWS; j++)
		{
			int posX = rand() % DISP_WIDTH;
			int posY = rand() % DISP_HEIGHT;

			paSmurfs[ ( i * SMURF_COLS_ROWS ) + j ] = new Sprite( ( i * smurfY ), ( j * smurfX ), smurfX, smurfY, pSmurfBuffer );
			gObject.draw(pColorBuffer, posX, posY, paSmurfs[i, j], NORM_SCALE);
		}
	}
	
	gObject.draw( pColorBuffer, 0, 0);

	//flip display
	gObject.flip();
	gObject.rest(SLEEP_TIME_IN_SECONDS);
	gObject.cleanup();
	gObject.saveBackBuffer(BACK_FILENAME);
	gObject.saveBuffer(pColorBuffer, COLOR_FILENAME);

	delete pStepsBuffer;
	delete pSmurfBuffer;
	delete pColorBuffer;
	delete textFont;

	for (int i = 0; i < NUM_SMURFS; i++)
	{
		delete paSmurfs[i];
	}

	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");

	return 0;

}