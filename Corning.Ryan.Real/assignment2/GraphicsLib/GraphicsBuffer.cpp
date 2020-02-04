#include "GraphicsBuffer.h"

GraphicsBuffer::GraphicsBuffer(ALLEGRO_BITMAP * bitmap)
{
	this->mBitmap = bitmap;
	this->toggleBitmap = true;
}

GraphicsBuffer::GraphicsBuffer(std::string & filename)
{
	mBitmap = al_load_bitmap(filename.c_str());
}

GraphicsBuffer::GraphicsBuffer(int width, int height, Color & color)
{
	//make the back the target
	ALLEGRO_BITMAP* backBitBuffer = al_get_target_bitmap();
	//create bitmap 
	mBitmap = al_create_bitmap(width, height);
	al_set_target_bitmap(mBitmap);
	mColor = al_map_rgb(color.getRValue(), color.getGValue(), color.getBValue());
	al_clear_to_color(mColor);
	//reset target
	al_set_target_bitmap(backBitBuffer);
}

GraphicsBuffer::~GraphicsBuffer()
{
	if (!toggleBitmap == true)
	{
		al_destroy_bitmap(mBitmap);
	}
}//
