/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include "Font.h"
#include "Sprite.h"

/*
This class is a graphics system that allows you to draw stuff to the screen
*/

class GraphicsSystem : public Trackable
{
private:
	ALLEGRO_DISPLAY * mpDisplay;
	GraphicsBuffer * mpBackbuffer;
	int mHeight;
	int mWidth;

public:

	//Constructor and destructor
	GraphicsSystem() {};

	~GraphicsSystem()
	{ 
		cleanup();
	};

	//Init and cleanup
	bool init(int width, int height);
	void cleanup();

	//Acessors
	int getHeight()
	{ 
		return mHeight;
	};

	int getWidth() 
	{
		return mWidth;
	};

	//Clear to color
	void clearToColor(Color color);

	//Draw functions
	void draw(Sprite * image, int x, int y);
	void draw(Sprite * image, int x, int y, int scale);
	void draw(Sprite * image, GraphicsBuffer * graphicsBuffer, int x, int y);
	void draw(Sprite * image, GraphicsBuffer * graphicsBuffer, int x, int y, int scale);

	void drawGraphicsBuffer(GraphicsBuffer * buffer, int x, int y);
	void drawGraphicsBuffer(GraphicsBuffer * buffer, int x, int y, float scale);
	void drawGraphicsBuffer(GraphicsBuffer * buffer, GraphicsBuffer * background, int x, int y);
	void drawGraphicsBuffer(GraphicsBuffer * buffer, GraphicsBuffer * background, int x, int y, float scale);

	//Text Functions
	void writeText(Font * font, int x, int y, Color color, std::string message);
	void writeText(Font * font, GraphicsBuffer * graphicsBuffer, int x, int y, Color color, std::string message);

	//Save functions
	void saveBuffer(GraphicsBuffer * graphicsBuffer, std::string fileName);
	void saveBackBuffer(std::string fileName);

	//Filp display
	void flip();

	//timer function
	void wait(float secounds);


	//Get the back buffer
	GraphicsBuffer * getBackBuffer();
};
