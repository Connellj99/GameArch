#ifndef GraphicsBuffer_H

#define GraphicsBuffer_H

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
#include "Colors.h"
#include "GraphicsBuffer.h"

#include <PerformanceTracker.h>
#include <MemoryTracker.h>



//Graphics Buffer ------------------------A class to hold a chunk of memory used to display something--------------------------------/
class GraphicsBuffer : public Trackable
{
public:
	friend class Game;
	friend class GraphicsSystem;
	friend class Sprite;
	friend class Animations;

	GraphicsBuffer();//default constructor
	GraphicsBuffer(Colors color,float xSize,float ySize);//constructor that takes in a Colors object
	GraphicsBuffer(std::string filePath);//constructor that takes in filepath for the img
	~GraphicsBuffer();//destructor

	float getBufferHeight();//function that returns buffer height

	float getBufferWidth();//function that returns buffer width

	void setBuffer(ALLEGRO_BITMAP*& bitmap);//set buffer really just sets the mBuffWidth/Height to the passed in buffers dimensions.

	//set the passed in bitmap and set it to this ones
	//void getBuffer(ALLEGRO_BITMAP& buffer);
	void getBuffer(GraphicsBuffer& buffer);

	//function that returns mBuffer
	ALLEGRO_BITMAP* returnBuff();

private:

	//Allegro bitmap mbuffer that will hold data of the allegro bitmap
	ALLEGRO_BITMAP* mpBuffer;
	ALLEGRO_BITMAP* mpBufferSprite;
	float mBuffHeight;
	float mBuffWidth;
};
#endif