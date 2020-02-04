#ifndef GRAPHICSBUFFER_H
#define GRAPHICSBUFFER_H


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

using namespace std;


class GraphicsBuffer : public Trackable
{
public:


	// Friends
	friend class GraphicsSystem;
	friend class Sprite;
	friend class GraphicsBufferManager;
	friend class Animation;

	// Destructors
	~GraphicsBuffer();

	// Acessor Functions
	int getHeight();
	int getWidth();


private:

	// Constructors
	GraphicsBuffer();
	GraphicsBuffer(string bitmapFilePath, string name);
	GraphicsBuffer(ALLEGRO_BITMAP * newBitmap, string name);
	GraphicsBuffer(int length, int height, Color colorOfScreen, string name);
	GraphicsBuffer(int length, int height, string name);

	bool mIsBackBuffer;

	string mName;

	// All allegro bitmaps
	ALLEGRO_BITMAP *mStoredBitmap;
};

#endif