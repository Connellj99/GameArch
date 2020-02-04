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

#include "GraphicsBuffer.h"

class Sprite : public Trackable
{
public:
	//constructors
	Sprite();
	Sprite(int sourceLocX, int sourceLocY, int width, int height, GraphicsBuffer* pGraphicsBuffer);
	~Sprite();
	//functions
	float getSourceLocX();
	float getSourceLocY();
	int getHeight();
	int getWidth();
	GraphicsBuffer* getGraphicsBuffer();

private:
	int mHeight;
	int mWidth;
	int mSourceLocX;
	int mSourceLocY;
	GraphicsBuffer* mpGraphicsBuffer;
};

