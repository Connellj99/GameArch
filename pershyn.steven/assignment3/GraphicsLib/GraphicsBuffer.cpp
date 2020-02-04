/*
Author: Steven Pershyn
Class: EGP-310-01
Assignment: Assignment 3
Certification of Authenticity: I certify that this assignment is my own work, except where I referenced classmates' work and mentioned where relevant.
*/
#include "GraphicsBuffer.h"

const std::string ASSET_PATH = "..\\..\\shared\\assets\\";
GraphicsBuffer::GraphicsBuffer()
{
	mpBitmap = NULL;
}

GraphicsBuffer::GraphicsBuffer(string bitmapName)
{
	//ownBitmap = true;
	mpBitmap = al_load_bitmap((ASSET_PATH + bitmapName).c_str());
	assert(mpBitmap);
	mWidth = al_get_bitmap_width(mpBitmap);
	mHeight = al_get_bitmap_height(mpBitmap);
}

GraphicsBuffer::GraphicsBuffer(string filePath, string fileName)
{
	init();
	mpBitmap = al_load_bitmap((filePath + fileName).c_str());
	assert(mpBitmap);
	//ownBitmap = true;
}

GraphicsBuffer::GraphicsBuffer(int width, int height, Color colorOfScreen)
{
	mpBitmap = al_create_bitmap(width, height);
	ALLEGRO_BITMAP * temp = al_get_target_bitmap();
	al_set_target_bitmap(mpBitmap);
	al_clear_to_color(al_map_rgb(colorOfScreen.getR(), colorOfScreen.getG(), colorOfScreen.getB()));
	al_set_target_bitmap(temp);
}

GraphicsBuffer::GraphicsBuffer(ALLEGRO_BITMAP * newBitmap, bool backBuffer)
{
	mpBitmap = newBitmap;
	mBackBuffer = backBuffer;
}


void GraphicsBuffer::init()
{
	if (!al_init())
	{
		cout << "Error initializing Allegro" << endl;
		return;
	}
	if (!al_init_image_addon())
	{
		cout << "Error initializing the Allegro image addon!" << endl;
		return;
	}
	return;
}

GraphicsBuffer::~GraphicsBuffer()
{
	if (mpBitmap != NULL) 
	{
		if(!mBackBuffer)
			al_destroy_bitmap(mpBitmap);
	}
}