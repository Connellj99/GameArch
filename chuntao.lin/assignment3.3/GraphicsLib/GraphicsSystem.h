#ifndef GraphicsSystem_H

#define GraphicsSystem_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "Colors.h"
#include "GraphicsBuffer.h"
#include "Font.h"
#include "Sprites.h"

#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <time.h> 

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

//this is just a const that is how many smurfs sprites there are in a row
const int SPRITESX = 4;

//GraphicsSystem ---------------------------The class which creates and maintains the display-----------------------/
class GraphicsSystem : public Trackable
{
	friend class System;

public:

	GraphicsSystem(int width, int height);//constructor that takes in the dimensions of display size
	~GraphicsSystem();//destructor

	int initGraphicSys();//initialize the graphic system and the display
	void cleanGraphicSys();//clean it up when donce.
	void waitDisplay();//function that rests 5 seconds
	//• Accessors(height, width, back buffer)
	int getGraphicSysHeight();//access the height

	int getGraphicSysWidth();//access the width

	void setBackBuffer();//access the backBuffer

	void flipDisplay();//call the al_flip function to display what is in the Back Buffer

	void drawBackBuffer(float xPos, float yPos,GraphicsBuffer& buffer, float scale);//takes in a buffer and draws to it

	void drawToGivenBuffer(GraphicsBuffer& targetBuffer, float xPos, float yPos, float scale);//takes in a buffer and draws to it

	void writeTextBackBuffer(float xPos, float yPos, Font& font, Colors& color, std::string theText);//takes in the parameters to write the font to the backbuffer

	void writeTextGraphicBuffer(GraphicsBuffer& targetBuffer, float xPos, float yPos, Font& font, Colors& color, std::string theText);//– write to given GraphicsBuffer

	void drawSmurfs(GraphicsBuffer& targetBuffer, float xPos, float yPos, float scale);

	void drawSprite(Sprite* passedSprite, float xPos, float yPos);//takes in the sprite and draws

	void saveBuffer(GraphicsBuffer& graphicBuffer, std::string outputFile);//– save the contents of a GraphicsBuffer to a file

	
private:

	//member data for the allegro display and dimensions
	ALLEGRO_DISPLAY * mpDisplay;
	
	int mWidth = 0;
	int mHeight = 0;

};
#endif