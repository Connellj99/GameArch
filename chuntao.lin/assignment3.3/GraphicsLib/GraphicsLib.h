#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

using namespace std;

//int initAllegro();

//GraphicsSystem ---------------------------The class which creates and maintains the display-----------------------/
class GraphicsSystem //: public Trackable
{
public:

	GraphicsSystem();
	~GraphicsSystem();

	int initGraphicSys();//• Init / Cleanup
	void cleanGraphicSys();

	float getGraphicSysHeight();//• Accessors(height, width, back buffer)

	float getGraphicSysWidth();

	void getBackBuffer();

	void flipDisplay();//	• Flip – call the al_flip function to display what is in the Back Buffer


protected:

	ALLEGRO_DISPLAY* mDisplay;

	void drawBackBuffer(float xPos, float yPos, ALLEGRO_BITMAP* sprite, float scale);
		/*
		• Draw(target graphics buffer, target loc, Sprite, scale /* default to 1.0 ) - draw to given
		GraphicsBuffer
		*/
	void drawToGivenBuffer(ALLEGRO_BITMAP* targetBuffer, float xPos, float yPos, ALLEGRO_BITMAP* sprite, float scale);

	void writeTextBackBuffer(float xPos, float yPos, ALLEGRO_FONT* font, ALLEGRO_COLOR* color, string theText);

	//void writeTextGraphicBuffer(ALLEGRO_BITMAP* graphicBuffer, float xPos, float yPos, ALLEGRO_FONT* font, ALLEGRO_COLOR* color, string theText);//– write to given GraphicsBuffer
	
	//void saveBuffer(ALLEGRO_BITMAP* graphicBuffer, string outputFile);//– save the contents of a GraphicsBuffer to a file
	float mWidth = 0;
	float mHeight = 0;
};

//Graphics Buffer ------------------------A class to hold a chunk of memory used to display something--------------------------------/
class GraphicsBuffer
{
public: 

	GraphicsBuffer();
	~GraphicsBuffer();

	void getBufferHeight();

	void getBufferWidth();

protected:

	ALLEGRO_BITMAP* mBuffer;

	float mBuffHeight;
	float mBuffWidth;
};

//Sprite------------------------A pointer to a specific part of a GraphicsBuffer--------------------------------/
class Sprite
{
public:

	Sprite();
	~Sprite();

	void getSpriteLocation();

	void getSpriteHeight();

	void getSpriteWidth();

	void getGraphicBuffer();

protected:

	const string ASSET_PATH = "..\\..\\shared\\assets\\";
	const string STEPS_FILENAME = "steps.png";
	const string DEAN_FILENAME = "dean_sprites.png";
	const string WOODS_FILENAME = "Woods.png";
	const string FONT_FILENAME = "cour.ttf";
	const int FONT_SIZE = 24;
	const string SAMPLE_FILENAME = "clapping.wav";

	ALLEGRO_BITMAP * graphicBufferBitmap;
	float locX;
	float locY;

	float spriteWidth;
	float spriteHeight;
};

//Font ----------------------------------------------------------------------------------------/
class Font
{
public:

	Font();
	~Font();

	void getSize();

protected:

	ALLEGRO_FONT* font;
	float fontSize;
};

//Colors struct to hold any colors I want to use
struct Colors
{
    const ALLEGRO_COLOR WHITE = al_map_rgb(255, 255, 255);
	const ALLEGRO_COLOR BLACK = al_map_rgb(0, 0, 0);
	const ALLEGRO_COLOR BLACK_TRANSPARENT = al_map_rgba(0, 0, 0, 200);
	const ALLEGRO_COLOR PURPLE = al_map_rgb(128, 64, 212);
};