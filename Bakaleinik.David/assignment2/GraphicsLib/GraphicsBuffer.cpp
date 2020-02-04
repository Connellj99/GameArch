#include "GraphicsBuffer.h"


GBuffer::~GBuffer()
{
	
	cleanup();
}

void GBuffer::cleanup()
{
	if (check == false)
	{
		al_destroy_bitmap(mpBitmap);
	}
	
}

GBuffer::GBuffer()
{

}

GBuffer::GBuffer(string path, string filename)
{
	mFilename = filename;
	mpBitmap = al_load_bitmap((path + mFilename).c_str());
	mHeight = al_get_bitmap_height(mpBitmap);
	mWidth = al_get_bitmap_width(mpBitmap);
	
	mBackgroundColor = al_map_rgb(0, 0, 0);
}

GBuffer::GBuffer(int height, int width, int r, int g, int b)
{
	mFilename = "";
	mHeight = height;
	mWidth = width;
	mBackgroundColor = al_map_rgb(r, g, b);
	mpBitmap = al_create_bitmap(mWidth, mHeight);
	
	ALLEGRO_BITMAP* temp = al_get_target_bitmap();

	al_set_target_bitmap(mpBitmap);
	al_clear_to_color(mBackgroundColor);
	al_set_target_bitmap(temp);

	al_save_bitmap("test.png", mpBitmap);
}

GBuffer::GBuffer(ALLEGRO_DISPLAY* pDisplay)
{
	mpBitmap = al_get_backbuffer(pDisplay);
	check = true;
}

int GBuffer::getHeight()
{
	return mHeight;
}

int GBuffer::getWidth()
{
	return mWidth;
}