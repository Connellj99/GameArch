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
#include <Trackable.h>

#include "GraphicsBuffer.h"
using namespace std;


class Sprite
{
public:
	Sprite();
	Sprite(int locX, int locY, int width, int height, GraphicsBuffer* graphicsBuffer);
	~Sprite();
	ALLEGRO_BITMAP* getBitmap();
	int getWidth();
	int getHeight();
	int getX();
	int getY();
	GraphicsBuffer* getGraphicsBuffer();

private:

	int mX;
	int mY;
	int mHeight;
	int mWidth;
	GraphicsBuffer* mpBitmap;
	GraphicsBuffer* mpGraphicsBuffer;
};