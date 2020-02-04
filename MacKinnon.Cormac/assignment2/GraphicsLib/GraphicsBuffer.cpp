#include "GraphicsBuffer.h"


//constructor for color, width, and height
GraphicsBuffer::GraphicsBuffer(int width, int height, Color &color)
{
	//mWidth = width;
	//mHeight = height;

	ALLEGRO_BITMAP *temp = al_get_target_bitmap();

	mpBitmap = al_create_bitmap(width, height);
	al_set_target_bitmap(mpBitmap);
	ALLEGRO_COLOR mColor = al_map_rgb(color.getR(), color.getG(), color.getB());
	al_clear_to_color(mColor);
	
	al_set_target_bitmap(temp);

	//mOwned = true;
}

//constructor for buffer based off of file name
GraphicsBuffer::GraphicsBuffer(std::string fileName)
{
	mpBitmap = al_load_bitmap(fileName.c_str());

	//mOwned = true;
}

//constructor for background buffer
GraphicsBuffer::GraphicsBuffer(ALLEGRO_BITMAP* pBitmapBackBuffer)
{
	mpBitmap = pBitmapBackBuffer;
	mOwned = true;
}

//destructor
GraphicsBuffer::~GraphicsBuffer()
{
	if (!mOwned) 
	{
		al_destroy_bitmap(mpBitmap);
	}
}

//height accessor
int GraphicsBuffer::getHeight() 
{
	return al_get_bitmap_height(mpBitmap);
}

//width accessor
int GraphicsBuffer::getWidth() 
{
	return al_get_bitmap_width(mpBitmap);
}

ALLEGRO_BITMAP* GraphicsBuffer::getBitmap() 
{
	return mpBitmap;
}
