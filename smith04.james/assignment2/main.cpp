#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <stdlib.h>

#include <GraphicsLib.h>

#include "Header.h"

using namespace std;

const string ASSET_PATH = "..\\..\\shared\\assets";

const int FONT_SIZE = 24;

const string TEXT = "Curse you Papa Smurf!";

const int NUM_SMURFS = 16;


int main()
{
	//initAllegro(); Done in Graphics System

	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;

	const string INIT_TRACKER_NAME = "init";
	const string DRAW_TRACKER_NAME = "draw";
	const string WAIT_TRACKER_NAME = "wait";

	const double SLEEP_TIME = 5.0;

	pPerformanceTracker->startTracking(INIT_TRACKER_NAME);

	MemoryTracker::getInstance()->reportAllocations(cout);

	GraphicsSystem* gSys = new GraphicsSystem();

	gSys->init();

	Color redColor;
	redColor.setR(255);
	Color blackColor;
	blackColor.setB(0);
	blackColor.setG(0);
	blackColor.setR(0);

	GraphicsBuffer* steps = new GraphicsBuffer((ASSET_PATH + "\\steps.png").c_str());

	GraphicsBuffer* smurfs = new GraphicsBuffer((ASSET_PATH + "\\smurf_sprites.png").c_str());

	GraphicsBuffer* red = new GraphicsBuffer();

	Font* font = new Font((ASSET_PATH + "\\cour.ttf").c_str(), FONT_SIZE);

	red->clearColor(redColor);

	gSys->writeText(red, 0, 0, font, blackColor, TEXT.c_str());

	red->draw(0, 0);

	steps->drawScaled(150.0, 100.0, 3.0); //Magic numbers because I can't figure out al_draw_scaled_bitmap works


	//float x, float y, float w, float h, GraphicsBuffer* buff

	Sprite* smurfList[NUM_SMURFS];

	for (int i = 0; i < NUM_SMURFS/4; i++)
	{
		for (int j = 0; j < NUM_SMURFS / 4; j++)
		{
			smurfList[(i*4) + j] = new Sprite(i * smurfs->getWidth() / 4.0, j * smurfs->getHeight() / 4.0, smurfs->getWidth() / 4.0, smurfs->getHeight() / 4.0, smurfs);
			smurfList[(i*4) + j]->draw(rand() % 600, rand() % 600);
		}
	}

	gSys->flip();

	pPerformanceTracker->stopTracking(DRAW_TRACKER_NAME);

	pPerformanceTracker->startTracking(WAIT_TRACKER_NAME);

	al_rest(SLEEP_TIME);

	pPerformanceTracker->stopTracking(WAIT_TRACKER_NAME);

	cout << endl << "Time to Init:" << pPerformanceTracker->getElapsedTime(INIT_TRACKER_NAME) << " ms" << endl;
	cout << endl << "Time to Draw:" << pPerformanceTracker->getElapsedTime(DRAW_TRACKER_NAME) << " ms" << endl;
	cout << endl << "Time spent waiting:" << pPerformanceTracker->getElapsedTime(WAIT_TRACKER_NAME) << " ms" << endl;

	delete pPerformanceTracker;

	delete steps;
	delete smurfs;
	delete red;
	delete font;

	for (int i = 0; i < NUM_SMURFS / 4; i++)
	{
		for (int j = 0; j < NUM_SMURFS / 4; j++)
		{
			delete smurfList[(i*4) + j];
		}
	}

	gSys->cleanup();
	delete gSys;

	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");

	return 0;

}