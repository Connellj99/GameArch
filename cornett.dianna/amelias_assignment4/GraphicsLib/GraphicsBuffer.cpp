/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#include "GraphicsBuffer.h"

GraphicsBuffer::GraphicsBuffer(int w, int h)
{
	mpBitmap = al_create_bitmap(w, h);
}

GraphicsBuffer::GraphicsBuffer()
{
};

GraphicsBuffer::GraphicsBuffer(std::string fileName)
{
	mpBitmap = al_load_bitmap(fileName.c_str());
}

GraphicsBuffer::GraphicsBuffer(ALLEGRO_BITMAP * bitmap, bool isBack)
{
	mIsBack = isBack;
	mpBitmap = bitmap;
}

GraphicsBuffer::~GraphicsBuffer()
{
	if (!mIsBack)
	{
		al_destroy_bitmap(mpBitmap);
	}
};


void GraphicsBuffer::GraphicsBuffer::clearToColor(Color color)
{
	ALLEGRO_BITMAP * temp = al_get_target_bitmap();
	al_set_target_bitmap(mpBitmap);
	al_clear_to_color(al_map_rgb(color.r, color.b, color.g));
	al_set_target_bitmap(temp);
}