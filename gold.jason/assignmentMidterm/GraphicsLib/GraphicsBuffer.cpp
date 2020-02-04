#include "GraphicsBuffer.h"
//const std::string ASSET_PATH = "..\\..\\shared\\assets\\";

GraphicsBuffer::GraphicsBuffer()
{
	mpBitmap = nullptr;
	mHeight = 0.0f;
	mWidth = 0.0f;
	mSetting = true;
}

GraphicsBuffer::GraphicsBuffer(std::string fileName, bool setting)
{
	mpBitmap = al_load_bitmap((fileName).c_str());
	mSetting = setting;
	mWidth = al_get_bitmap_width(mpBitmap);
	mHeight = al_get_bitmap_height(mpBitmap);
}

GraphicsBuffer::GraphicsBuffer(float height, float width, Color color, bool setting)
{
	mpBitmap = al_create_bitmap(width, height);
	al_clear_to_color(al_map_rgb(color.getColor().r, color.getColor().g, color.getColor().b));
	mSetting = setting;
	mWidth = width;
	mHeight = height;
}

GraphicsBuffer::GraphicsBuffer(ALLEGRO_BITMAP* bitmapPointer, bool setting)
{
	mpBitmap = bitmapPointer;
	mSetting = setting;
	//mWidth = al_get_bitmap_width(mpBitmap);
	//mHeight = al_get_bitmap_height(mpBitmap);
}

GraphicsBuffer::~GraphicsBuffer()
{
	if (mSetting)
	{
		al_destroy_bitmap(mpBitmap);
	}
}
