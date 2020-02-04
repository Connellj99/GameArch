#include "GraphicsBuffer.h"
//create buffer with color and location
GraphicsBuffer::GraphicsBuffer(Vector2D size, Color color)
{
	mpBitmap = al_create_bitmap(size.getX(),size.getY());
	assert(mpBitmap);

	ALLEGRO_BITMAP* tempBitmap = al_get_target_bitmap();
	al_set_target_bitmap(mpBitmap);
	al_clear_to_color(color.getColor());
	al_set_target_bitmap(tempBitmap);
}
//load buffer from file
GraphicsBuffer::GraphicsBuffer(string filename)
{
	mpBitmap = al_load_bitmap(filename.c_str());
}
//destroy bitmap
GraphicsBuffer::~GraphicsBuffer()
{
	al_destroy_bitmap(mpBitmap );
}
//retun width
int GraphicsBuffer::getWidth()
{
	return al_get_bitmap_width(mpBitmap);
}
//return height
int GraphicsBuffer::getHeight()
{
	return al_get_bitmap_height(mpBitmap);
}
