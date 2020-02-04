/*
Miller Roman
EGP-310-01
Assigment 2
*/

#include <iostream>
#include <cassert>
#include <string>
#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <GraphicsSystem.h>
#include <Vector2D.h>
using namespace std;

int main()
{
	const float REST_TIME = 5.0;

	const Vector2D SCREEN_SIZE(800, 600);
	const string ASSET_PATH = "..\\..\\shared\\assets\\";
	const string FONT_FILENAME = "cour.ttf";
	const string STEPS_FILENAME = "steps.png";
	const string SMURF_FILENAME = "smurf_sprites.png";
	const string BUFFER_LOCATION = "..\\..\\Roman.Miller\\assignment2\\";
	const string BACKBUFFER_SAVE_FILENAME = "backbuffer.jpg";
	const string REDBUFFER_SAVE_FILENAME = "redbuffer.jpg";

	
	
	const float STEPS_IMAGE_SCALE = 2 / 3.0f;

	const Vector2D SMURFS_LAYOUT(4, 4);
	const Vector2D SMURF_SPRITE_SIZE(60, 60);

	const Vector2D TEXT_LOC(0, 0);
	const int FONT_SIZE = 25;
	string TEXT_TO_SCREEN = "Curse you Papa Smurf!!!";

	//------------------------------------------------------------------------------

	//Create graphics system, red buffer and font
	auto graphicsSystem = GraphicsSystem();
	graphicsSystem.init();
	const Color RED(255, 0, 0, 255);
	const Color BLACK(0, 0, 0, 255);
	const Color WHITE(255, 255, 255, 255);
	auto redGraphicsBuffer = new GraphicsBuffer(SCREEN_SIZE, RED);
	auto font = new Font(ASSET_PATH, FONT_FILENAME, FONT_SIZE);
	 
	//write curse you papa smurf
	graphicsSystem.writeText(*redGraphicsBuffer,TEXT_LOC.getX(), TEXT_LOC.getY(), *font, BLACK, TEXT_TO_SCREEN);
	//make a red sprite
	auto spriteRed = new Sprite(redGraphicsBuffer, Vector2D(0, 0), SCREEN_SIZE);
	graphicsSystem.draw(Vector2D(0,0), *spriteRed);
	//load steps image and set it to a buffer
	auto steps = new GraphicsBuffer(ASSET_PATH + STEPS_FILENAME);
	auto stepsSprite = new Sprite(steps, Vector2D(0, 0), SCREEN_SIZE);
	graphicsSystem.draw(Vector2D(SCREEN_SIZE*0.5 - SCREEN_SIZE * STEPS_IMAGE_SCALE * 0.5), *stepsSprite, STEPS_IMAGE_SCALE);
	//load in smurf sprite sheet
	auto smurfBuffer = new GraphicsBuffer(ASSET_PATH + SMURF_FILENAME);
	
	//take each smurf from the sheet (nested loop for x and y)
	for (int i = 0;  i < SMURFS_LAYOUT.getX(); i++)
	{
		for (int j = 0; j < SMURFS_LAYOUT.getY(); j++)
		{
			auto smurf = new Sprite(smurfBuffer, Vector2D(i*SMURF_SPRITE_SIZE.getX(), j*SMURF_SPRITE_SIZE.getY()), SMURF_SPRITE_SIZE);
			//set to a random vec2 location on screen
			Vector2D location = (rand() % int(SCREEN_SIZE.getX() - SMURF_SPRITE_SIZE.getX()*0.5f), rand() % int(SCREEN_SIZE.getX() - SMURF_SPRITE_SIZE.getY()*0.5f));
			graphicsSystem.draw(location, *smurf, 1);
			delete smurf;
		}
	}
	//safe buffers to file with name
	graphicsSystem.saveBuffer(*redGraphicsBuffer,REDBUFFER_SAVE_FILENAME);
	graphicsSystem.saveBuffer(BACKBUFFER_SAVE_FILENAME);
	
	//display the back buffer/wait 
	graphicsSystem.flip();
	graphicsSystem.rest(5); //CHANGE BACK
	graphicsSystem.cleanUp();

	//delete memory---
	delete smurfBuffer;
	delete font;
	delete spriteRed;
	delete redGraphicsBuffer;
	delete steps;
	delete stepsSprite;


	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");
	return 0;
}