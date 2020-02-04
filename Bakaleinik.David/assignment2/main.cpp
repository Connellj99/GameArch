

/*
Author: David Bakaleinik
Class: EGP-310
Assignment: PA 02
Date Assigned: 01/25/2019 - 12:30pm
Due Date: 02/01/2019 - 12:01pm
Description:
Encapsualtion of allegro functionality inside a number of classes, which are located in a library.

Certification of Authenticity:
I certify that this is entirely my own work, except where I have given
fully-documented references to the work of others. I understand the
definition and consequences of plagiarism and acknowledge that the assessor
of this assignment may, for the purpose of assessing this assignment:
- Reproduce this assignment and provide a copy to another member of
academic staff; and/or
- Communicate a copy of this assignment to a plagiarism checking
service (which may then retain a copy of this assignment on its
database for the purpose of future plagiarism checking)
*/


#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Font.h"
#include "GraphicsLib.h"


using namespace std;

int main()
{
	srand(time(NULL));
	
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;

	const string ASSET_PATH = "..\\..\\shared\\assets\\";
	string messageText = "Curse you Papa Smurf!";
	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;
	const int FONT_SIZE = 24;
	const string PICTURE_FILENAME = "steps.png";
	const string SPRITE_FILENAME = "smurf_sprites.png";
	const string FONT_FILENAME = "cour.ttf";

	const string INIT_TRACKER_NAME = "init";
	const string DRAW_TRACKER_NAME = "draw";
	const string WAIT_TRACKER_NAME = "wait";

	
	pPerformanceTracker->startTracking(INIT_TRACKER_NAME);
	GSystem *displayScreen = new GSystem(DISP_HEIGHT, DISP_WIDTH);
	pPerformanceTracker->stopTracking(INIT_TRACKER_NAME);
	displayScreen->initDisplay();
	
	pPerformanceTracker->startTracking(DRAW_TRACKER_NAME);
	GBuffer *redBG = new GBuffer(DISP_HEIGHT, DISP_WIDTH, 255, 0, 0);
	Sprite *red = new Sprite(redBG, 0, 0, DISP_HEIGHT, DISP_WIDTH);

	Font *textFont = new Font(ASSET_PATH, FONT_FILENAME, FONT_SIZE);
	
	GBuffer *spriteMap = new GBuffer(ASSET_PATH, SPRITE_FILENAME);

	GBuffer *steps = new GBuffer(ASSET_PATH, PICTURE_FILENAME);
	Sprite *stepsSprite = new Sprite (steps, 0, 0, steps->getHeight(), steps->getWidth());

	
	displayScreen->writeText(redBG, 0, 0, textFont, 0, 0, 0, messageText);
	displayScreen->draw(0, 0, red, 1.0);
	

	displayScreen->draw(140, 100, stepsSprite, (1.0f/3.0f));

	Sprite *spriteArray[16];
	for (int i = 0; i < 4; i ++)
	{
		for (int j = 0; j < 4; j ++)
		{
			
			spriteArray[i*4+j] = new Sprite(spriteMap, (spriteMap->getWidth()/4)*i, (spriteMap->getHeight()/4)*j, 60, 60);
			
		}
	}

	for (int i = 0; i < 16; i++)
	{
		int posX = rand() % 600 + 1;
		int posY = rand() % 600 + 1;
		displayScreen->draw(posX, posY, spriteArray[i], 1, 60, 60, spriteArray[i]->getHeight(), spriteArray[i]->getWidth());
	}
	

	pPerformanceTracker->stopTracking(DRAW_TRACKER_NAME);
	//make display 800x600
	//make graphicsBuffer01 w/ PICTURE_FILENAME
	//make graphicsBuffer02 w/ SPRITE_FILENAME
	//make graphicsBuffer03 w/ RED
		//Add MESSAGE_TEXT to graphicsBuffer03
	//Draw graphicsBuffer03 onto the display
	//Draw graphicsBuffer02 scaled down by 1/3
	//Draw sprites onto display
		//split SPRITE_FILENAME file into 16 images
		//draw them in random positions
	//Use GraphicsSystem::saveBuffer to save screen to backbuffer.jpg
	//Use GraphicsSystem::saveBuffer to save graphicsBuffer03 as redbuffer.jpg)  
	//close display after 5 sec
	
	displayScreen->flipDispaly();
	pPerformanceTracker->startTracking(WAIT_TRACKER_NAME);
	displayScreen->waitForSeconds(5.0);
	pPerformanceTracker->stopTracking(WAIT_TRACKER_NAME);

	

	

	//report elapsed times
	cout << endl << "Time to Init:" << pPerformanceTracker->getElapsedTime(INIT_TRACKER_NAME) << " ms" << endl;
	cout << endl << "Time to Draw:" << pPerformanceTracker->getElapsedTime(DRAW_TRACKER_NAME) << " ms" << endl;
	cout << endl << "Time spent waiting:" << pPerformanceTracker->getElapsedTime(WAIT_TRACKER_NAME) << " ms" << endl;

	for (int i = 0; i < 16; i++)
	{
		delete spriteArray[i];
	}

	delete stepsSprite;
	delete steps;
	delete spriteMap;
	delete textFont;
	delete red;
	delete redBG;
	delete displayScreen;

	

	delete pPerformanceTracker;


	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");

	return 0;

}