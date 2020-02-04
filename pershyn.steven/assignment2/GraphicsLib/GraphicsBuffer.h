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

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <Trackable.h>
#include "Color.h"

using namespace std;

class GraphicsBuffer : public Trackable
{
	friend class GraphicsSystem;
public:
	GraphicsBuffer();
	GraphicsBuffer(string bitmapFilePath);
	GraphicsBuffer(int width, int height, Color colorofScreen);
	GraphicsBuffer(ALLEGRO_BITMAP* newBitmap, bool backBuffer);
	~GraphicsBuffer();
	int getHeight();
	int getWidth();

private:
	ALLEGRO_BITMAP *mpBitmap;
	ALLEGRO_BITMAP *getBitmap();
	bool mBackBuffer = false;
};