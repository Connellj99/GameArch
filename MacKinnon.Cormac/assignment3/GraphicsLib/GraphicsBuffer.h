#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include "Color.h"

class GraphicsBuffer : public Trackable
{

public:
	friend class GraphicsSystem;
	//constructors
	GraphicsBuffer(std::string fileName);
	GraphicsBuffer(int width, int height, Color &color);
	~GraphicsBuffer();

	//accessors
	int getHeight();
	int getWidth();
	

private:
	GraphicsBuffer(ALLEGRO_BITMAP* pBitmapBackBuffer);
	bool mOwned;
	ALLEGRO_BITMAP* getBitmap();
	//int mHeight;
	//int mWidth;
	ALLEGRO_BITMAP* mpBitmap;

};

