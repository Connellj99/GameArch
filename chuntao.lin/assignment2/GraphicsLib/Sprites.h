#ifndef Sprites_H

#define Sprites_H

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
#include "GraphicsBuffer.h"

//consts that contain any and all asset paths in the shared folder
const std::string ASSET_PATH = "..\\..\\shared\\assets\\";
const std::string STEPS_FILENAME = "steps.png";
const std::string DEAN_FILENAME = "dean_sprites.png";
const std::string WOODS_FILENAME = "Woods.png";
const std::string FONT_FILENAME = "cour.ttf";
const int FONT_SIZE = 24;

//Sprite------------------------A pointer to a specific part of a GraphicsBuffer--------------------------------/
class Sprite : public Trackable
{
	
public:

	friend class GraphicsSystem;
	friend class GraphicsBuffer;

	Sprite();//default constructor
	~Sprite();//destructor

	void setSpriteSteps(GraphicsBuffer& buffer);//sets the graphicSpriteBitmap to a new sprite image
	void setSpriteSmurfDean(GraphicsBuffer& buffer);//sets the graphicSpriteBitmap to a new sprite image
	
	//void setSpriteSourceLocation(float xPos, float yPos);//gets and sets the starting sprite locations
	void setSpriteSourceLocation(GraphicsBuffer& buffer);//gets and sets the starting sprite locations
	float getSpriteSourceLocationX();
	float getSpriteSourceLocationY();

	void setSpriteHeight();//sets m sprite height to the bitmap's height
	void setSpriteWidth();//sets m sprite height to the bitmap's width

	float getSpriteHeight();//sets m sprite height to the bitmap's height
	float getSpriteWidth();//sets m sprite height to the bitmap's width

	int getNumOfSmurfs();//gets the number of total smurfs
	int getNumOfSmurfsX();//gets number of smurfs in a row
	int getNumOfSmurfsY();//gets number of smurfs in a column

	void addNumOfSmurfs();//Adds to the number of total smurfs
	void addNumOfSmurfsX();//Adds to the number of smurfs in a row
	void addNumOfSmurfsY();//Adds to the number of smurfs in a column

	void resetNumOfSmurfsX();//Resets number of X Smurfs
	void resetNumOfSmurfsY();//Resets number of X Smurfs

	GraphicsBuffer graphicBuffObject;//class object of Graphics Buffer

private:

	ALLEGRO_BITMAP* graphicSpriteBitmap;//a pointer to the bitmap

	GraphicsBuffer* getGraphicBuffer();//pointer that reutns the graphicsBuffer class object

	//members for the sprite and its size and source position.
	float mSpriteWidth;
	float mSpriteHeight;
	float mLocX;
	float mLocY;

	//used for determining how many sprites there are overall and in rows and columns
	//set to -1 because of a mathematical counter so itll be current number of sprites -1.
	int mNumSmurfSprites = 0;
	int mNumSmurfsX = 0;
	int mNumSmurfsY = 0;

	//bool that checks if its time to destroy or not
	bool mBitMapInUse = true;
	
};
#endif