/*
Conner Root
EGP 310-01
*/

#include "GraphicsBuffer.h"

// Constructor
GraphicsBuffer::GraphicsBuffer()
{
	mpBitmap = nullptr;
}
GraphicsBuffer::GraphicsBuffer(ALLEGRO_BITMAP* bitmap)
{
	mpBitmap = bitmap;
}
GraphicsBuffer::GraphicsBuffer(const string& fileName)
{
	mpBitmap = al_load_bitmap(fileName.c_str());
	mFilename = fileName;
}
GraphicsBuffer::GraphicsBuffer(string& filename, int width, int height, Color color)
{
	ALLEGRO_BITMAP* initBitmap = al_get_target_bitmap();

	mpBitmap = al_create_bitmap(width, height);

	al_set_target_bitmap(mpBitmap);

	al_clear_to_color(color.getColor());

	al_set_target_bitmap(initBitmap);

	mFilename = filename;
}

// Cleanup
void GraphicsBuffer::cleanup()
{
	al_destroy_bitmap(mpBitmap);
}

// Accessors
int GraphicsBuffer::getWidth()
{
	return al_get_bitmap_width(mpBitmap);
}

int GraphicsBuffer::getHeight()
{
	return al_get_bitmap_height(mpBitmap);
}

ALLEGRO_BITMAP* GraphicsBuffer::getBitmap()
{
	return mpBitmap;
}

string GraphicsBuffer::getFileName()
{
	return mFilename;
}

// Destructor
GraphicsBuffer::~GraphicsBuffer()
{
	cleanup();
}