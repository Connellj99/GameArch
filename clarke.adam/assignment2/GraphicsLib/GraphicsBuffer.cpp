#include "GraphicsBuffer.h"

GraphicsBuffer::GraphicsBuffer(const std::string& filename)
{
	mpBitmap = al_load_bitmap(filename.c_str());
	assert(mpBitmap);
}

GraphicsBuffer::GraphicsBuffer(const Vector2D& dimensions, const Color& color)
{
	mpBitmap = al_create_bitmap(dimensions.getX(), dimensions.getY());
	assert(mpBitmap);

	// set only this buffer's bitmap to color
	const auto initTargetBitmap = al_get_target_bitmap();
	al_set_target_bitmap(mpBitmap);
	al_clear_to_color(color.getAllegroColor());
	al_set_target_bitmap(initTargetBitmap);
}

GraphicsBuffer::GraphicsBuffer(ALLEGRO_BITMAP* bitmap)
{
	mpBitmap = bitmap;
	assert(bitmap);
}


GraphicsBuffer::~GraphicsBuffer()
{
	al_destroy_bitmap(mpBitmap);
}