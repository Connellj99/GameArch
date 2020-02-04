#include "GraphicsBuffer.h"


GraphicsBuffer::GraphicsBuffer()
{
	mpBitmap = NULL;
}

GraphicsBuffer::GraphicsBuffer(string bitmapFilePath)
{
	mpBitmap = al_load_bitmap(bitmapFilePath.c_str());
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


int GraphicsBuffer::getHeight()
{
	return al_get_bitmap_height(mpBitmap);
}

int GraphicsBuffer::getWidth()
{
	return al_get_bitmap_width(mpBitmap);
}

ALLEGRO_BITMAP * GraphicsBuffer::getBitmap()
{
	return mpBitmap;
}

GraphicsBuffer::~GraphicsBuffer()
{
	if (mpBitmap != NULL) 
	{
		if(!mBackBuffer)
			al_destroy_bitmap(mpBitmap);
	}
}