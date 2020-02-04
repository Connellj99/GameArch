#include "GraphicsBuffer.h"

GraphicsBuffer::GraphicsBuffer()
{
	mpBitmap = al_create_bitmap(600, 800);
}

GraphicsBuffer::GraphicsBuffer(const char* assetPath)
{
	mpBitmap = al_load_bitmap(assetPath);
	assert(mpBitmap);
}

GraphicsBuffer::GraphicsBuffer(ALLEGRO_BITMAP* bitmap)
{
	mpBitmap = bitmap;
	assert(mpBitmap);
}

GraphicsBuffer::~GraphicsBuffer()
{
	al_destroy_bitmap(mpBitmap);
}

float GraphicsBuffer::getHeight()
{
	return al_get_bitmap_height(mpBitmap);
}

float GraphicsBuffer::getWidth()
{
	return al_get_bitmap_width(mpBitmap);
}

ALLEGRO_BITMAP* GraphicsBuffer::getBitMap()
{
	return mpBitmap;
}

void GraphicsBuffer::clearColor(Color c)
{
	al_clear_to_color(c.getColor());
}

void GraphicsBuffer::draw(float x, float y)
{
	al_draw_bitmap(mpBitmap, x, y, 0);
}

void GraphicsBuffer::drawScaled(float x, float y, float s)
{
	al_draw_scaled_bitmap(mpBitmap, x, y, getWidth() / s, getHeight() / s, x, y, getWidth() / s, getHeight() / s, 0);
}