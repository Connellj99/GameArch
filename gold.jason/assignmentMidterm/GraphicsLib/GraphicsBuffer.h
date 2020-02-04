#ifndef GraphicsBuffer_h
#define GraphicsBuffer_h

#include "Trackable.h"
#include <allegro5\allegro.h>
#include "Color.h"

//dont pass by value
class GraphicsBuffer: public Trackable
{
public:
	GraphicsBuffer();
	GraphicsBuffer(std::string fileName, bool setting);
	GraphicsBuffer(float width, float height, Color color, bool setting);
	GraphicsBuffer(ALLEGRO_BITMAP* bitmapPointer, bool setting);
	~GraphicsBuffer();
	friend class GraphicsSystem;
	/*
	graphicsbuffer constructors
	1 file in (true)
	2 size, and color (true)
	3 Allegro_Bitmap (false) 
	*/
	float getHeight()
	{
		return mHeight;
	};
	float getWidth()
	{ 
		return mWidth;
	};


private:

	ALLEGRO_BITMAP* getBitmap()
	{
		return mpBitmap;
	};

	ALLEGRO_BITMAP *mpBitmap;
	float mHeight;
	float mWidth;
	bool mSetting;
	//allegro bitmap pointer
};
#endif // GraphicsBuffer_h