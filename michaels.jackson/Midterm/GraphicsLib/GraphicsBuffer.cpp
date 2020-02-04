/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Assignment 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "GraphicsBuffer.h"
#include "Color.h"
/*#################################
			GraphicsBuffer
#################################*/

GraphicsBuffer::GraphicsBuffer(std::string mapName, bool fromAssets) 
{
	mOwnsBitmap = true;
	if (fromAssets)
		mBitmap = al_load_bitmap((ASSET_PATH + mapName).c_str());
	else
		mBitmap = al_load_bitmap((mapName).c_str());
	assert(mBitmap);

	mWidth = al_get_bitmap_width(mBitmap);
	mHeight = al_get_bitmap_height(mBitmap);

}
GraphicsBuffer::GraphicsBuffer(int wide, int tall) 
{
	mOwnsBitmap = true;
	mBitmap = al_create_bitmap(wide, tall);
	assert(mBitmap);

	mWidth = wide;
	mHeight = tall;
}

GraphicsBuffer::GraphicsBuffer(ALLEGRO_BITMAP* map) 
{
	mOwnsBitmap = false;
	mBitmap = map;
	mWidth = al_get_bitmap_width(mBitmap);
	mHeight = al_get_bitmap_height(mBitmap);	
}


GraphicsBuffer::~GraphicsBuffer() 
{
	if (mOwnsBitmap)
	{
		al_destroy_bitmap(mBitmap);
	}
}

void GraphicsBuffer::setColor(Color* color) 
{
	ALLEGRO_BITMAP* old = al_get_target_bitmap();
	al_set_target_bitmap(mBitmap);
	al_clear_to_color(color->mAlColor);
	al_draw_bitmap(mBitmap, 0, 0, 0);
	al_set_target_bitmap(old);
}